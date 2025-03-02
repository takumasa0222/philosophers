#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>

// 定数定義（単位：ミリ秒）
#define NUM_PHILOSOPHERS 2
#define EAT_TIME    100   // 食事時間
#define SLEEP_TIME  100  // 睡眠時間
#define THINK_TIME  0     // 思考時間（今回与えられていないので0）
#define TIME_LIMIT  (EAT_TIME + SLEEP_TIME + 210)  // 死亡条件：300ms

// 共有データ構造体（グローバル変数禁止のため、main内で確保）
typedef struct {
    pthread_mutex_t meal_mutex;              // 最後の食事時刻保護用
    long last_meal_time[NUM_PHILOSOPHERS];     // 各哲学者の最後の食事時刻
    int stop;                                // シミュレーション停止フラグ（0: 継続, 1: 停止）
    pthread_mutex_t stop_mutex;              // stop フラグ保護用
} SharedData;

// 各哲学者の情報
typedef struct {
    int id;                    // 0～NUM_PHILOSOPHERS-1
    pthread_mutex_t *forks;    // フォークの配列（サイズ＝NUM_PHILOSOPHERS）
    SharedData *shared;        // 共有データ
} Philosopher;

// 現在時刻をミリ秒単位で返す
long get_current_time(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

// stop フラグを設定する
void set_stop(SharedData *shared) {
    pthread_mutex_lock(&shared->stop_mutex);
    shared->stop = 1;
    pthread_mutex_unlock(&shared->stop_mutex);
}

// stop フラグをチェックする（1なら停止）
int is_stopped(SharedData *shared) {
    int ret;
    pthread_mutex_lock(&shared->stop_mutex);
    ret = shared->stop;
    pthread_mutex_unlock(&shared->stop_mutex);
    return ret;
}

// 監視スレッド：1ms ごとに各哲学者の最後食事時刻をチェックし、TIME_LIMIT を超えたら stop フラグをセット
void *monitor_thread(void *arg) {
    SharedData *shared = (SharedData *)arg;
    while (!is_stopped(shared)) {
        usleep(1000);  // 1ms待機
        long now = get_current_time();
        pthread_mutex_lock(&shared->meal_mutex);
        for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
            if (now - shared->last_meal_time[i] > TIME_LIMIT) {
                printf("Philosopher %d has died (last meal %ld ms ago). Stopping simulation.\n", 
                       i+1, now - shared->last_meal_time[i]);
                pthread_mutex_unlock(&shared->meal_mutex);
                set_stop(shared);
                return NULL;
            }
        }
        pthread_mutex_unlock(&shared->meal_mutex);
    }
    return NULL;
}

// 各哲学者のスレッド：食事→睡眠のループ（思考時間は0）
void *philosopher_thread(void *arg) {
    Philosopher *phil = (Philosopher *)arg;
    int left_fork = phil->id;
    int right_fork = (phil->id + 1) % NUM_PHILOSOPHERS;
	int	temp;

	if (left_fork > right_fork)
	{
		temp = left_fork;
		left_fork = right_fork;
		right_fork = temp;
	}
    
    while (!is_stopped(phil->shared)) {
        // 思考時間は0なので、すぐに食事へ
        
        // フォークの取得（ブロッキングロック）
        pthread_mutex_lock(&phil->forks[left_fork]);
        pthread_mutex_lock(&phil->forks[right_fork]);
        
        // 食事を開始する前に、最後食事時刻を更新
        pthread_mutex_lock(&phil->shared->meal_mutex);
        phil->shared->last_meal_time[phil->id] = get_current_time();
        pthread_mutex_unlock(&phil->shared->meal_mutex);
        
        printf("Philosopher %d is eating.\n", phil->id + 1);
        usleep(EAT_TIME * 1000);  // 食事中
        
        // フォークを解放
        pthread_mutex_unlock(&phil->forks[right_fork]);
        pthread_mutex_unlock(&phil->forks[left_fork]);
        
		if (is_stopped(phil->shared)) break;
        
        // 睡眠
        printf("Philosopher %d is sleeping.\n", phil->id + 1);
        usleep(SLEEP_TIME * 1000);
    }
    
    printf("Philosopher %d exiting.\n", phil->id + 1);
    return NULL;
}

int main(void) {
    int i;
    pthread_t phil_threads[NUM_PHILOSOPHERS];
    pthread_t monitor_tid;
    
    // 共有データの動的確保と初期化（グローバル変数は使わず、main内で管理）
    SharedData *shared = (SharedData *)malloc(sizeof(SharedData));
    memset(shared, 0, sizeof(SharedData));  // stop=0, last_meal_time初期値=0
    pthread_mutex_init(&shared->meal_mutex, NULL);
    pthread_mutex_init(&shared->stop_mutex, NULL);
    shared->stop = 0;
    
    // フォークの配列を動的に確保（各フォークは main 内のローカル領域）
    pthread_mutex_t *forks = (pthread_mutex_t *)malloc(NUM_PHILOSOPHERS * sizeof(pthread_mutex_t));
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }
    
    // 初期の最後食事時刻は全員とも現在時刻に設定
    long now = get_current_time();
    pthread_mutex_lock(&shared->meal_mutex);
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        shared->last_meal_time[i] = now;
    }
    pthread_mutex_unlock(&shared->meal_mutex);
    
    // 各哲学者のデータをローカル配列で確保
    typedef struct {
        Philosopher phil;
    } PhilosopherWrapper;
    
    PhilosopherWrapper *phils = (PhilosopherWrapper *)malloc(NUM_PHILOSOPHERS * sizeof(PhilosopherWrapper));
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        phils[i].phil.id = i;
        phils[i].phil.forks = forks;
        phils[i].phil.shared = shared;
        pthread_create(&phil_threads[i], NULL, philosopher_thread, (void *)&phils[i].phil);
    }
    
    // 監視スレッドの作成
    pthread_create(&monitor_tid, NULL, monitor_thread, (void *)shared);
    
    // 各哲学者のスレッドの終了を待機
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(phil_threads[i], NULL);
    }
    pthread_join(monitor_tid, NULL);
    
    // リソースの解放
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }
    free(forks);
    pthread_mutex_destroy(&shared->meal_mutex);
    pthread_mutex_destroy(&shared->stop_mutex);
    free(shared);
    free(phils);
    
    return 0;
}
