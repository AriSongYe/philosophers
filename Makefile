# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yecsong <yecsong@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/30 06:35:21 by yecsong           #+#    #+#              #
#    Updated: 2022/12/09 16:15:06 by yecsong          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo

SRCS := new_philo.c\

OBJS := $(SRCS:%.c=%.o)

CC := cc

CFLAGS := -Werror -Wextra -Wall -pthread

all : $(NAME)


$(NAME) : $(OBJS)
		$(CC) $(CFLAGS) $(SRCS) ./libft/libft.a  -o philo

re : fclean all

clean :
	rm -f *.o
	rm -f libft/*.o

fclean : clean
	rm -f $(NAME)
	rm -f libft/libft.a

bonus :

.PHONY : all clean fclean bonus re
