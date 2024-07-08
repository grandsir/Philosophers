# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: databey <databey@student.42kocaeli.com.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/06 11:02:35 by databey           #+#    #+#              #
#    Updated: 2024/07/08 16:47:37 by databey          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= philo.c dinner.c initialization.c utils.c parse.c get.c errors.c thread.c write.c philosophers.c
OBJS	= $(SRCS:.c=.o)
NAME	= philo
GCC	= gcc
FLAGS	= -Wall -Wextra -Werror
INCLUDE	= -lpthread
HEADER	= philo.h

all:	$(NAME)

%.o: %.c $(HEADER)
	$(GCC) $(FLAGS) -c $<  -o $(<:.c=.o)

$(NAME): $(OBJS)
	$(GCC) $(INCLUDE) $(FLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS) $(B_OBJS)
fclean: clean
	rm -f $(NAME) $(BONUS)
re: fclean all

.PHONY:	clean fclean re all
