# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yecsong <yecsong@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/05 10:24:59 by yecsong           #+#    #+#              #
#    Updated: 2022/12/05 10:31:23 by yecsong          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := practice

SRCS := create_philo.c

OBJS := $(SRCS:%.c=%.o)

CFLAGS := -Werror -Wextra -Wall -pthread

CC := cc

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(SRCS) -o practice

