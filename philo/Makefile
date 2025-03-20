# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/25 21:34:48 by shokosoeno        #+#    #+#              #
#    Updated: 2025/03/20 18:41:41 by tamatsuu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
INCLUDES = -I includes 
CFLAGS = -Wall -Wextra -Werror -g $(INCLUDES) 


SRCS = \
srcs/main.c \
srcs/monitor/monitor.c \
srcs/philosophers/dining_philo.c \
srcs/philosophers/init_philo.c \
srcs/philosophers/philosophers_actions.c \
srcs/philosophers/prepare_philo_resources.c \
srcs/philosophers/prepare_philo_resources_2.c \
srcs/utils/ft_strtol.c \
srcs/utils/input_validator.c \
srcs/utils/printer.c \
srcs/utils/time_calculation.c \
srcs/utils/value_checker.c \
srcs/utils/free_func.c 


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