# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tamatsuu <tamatsuu@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/25 21:34:48 by shokosoeno        #+#    #+#              #
#    Updated: 2025/03/05 01:04:46 by tamatsuu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
INCLUDES = -I includes 
CFLAGS = -Wall -Wextra -Werror -g $(INCLUDES) 


SRCS = \
srcs/main.c \
srcs/monitor/monitor.c \
srcs/philosophers/destroy_resources.c \
srcs/philosophers/dining_philo.c \
srcs/philosophers/init_philo.c \
srcs/philosophers/philosophers_actions.c \
srcs/philosophers/prepare_philo_resources.c \
srcs/utils/ft_strtol.c \
srcs/utils/input_validator.c \
srcs/utils/printer.c \
srcs/utils/time_calculation.c \
srcs/utils/value_checker.c 


OBJS = $(SRCS:.c=.o)

# General rules

all: $(NAME)


$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lpthread

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

norm:
	norminette -R CheckForbiddenSourceHeader $(SRCS) 

.PHONY: all clean fclean re test