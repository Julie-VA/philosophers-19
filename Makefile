# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/13 12:16:45 by rvan-aud          #+#    #+#              #
#    Updated: 2021/11/01 14:37:59 by rvan-aud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= 	srcs/main.c			\
			srcs/actions.c		\
			srcs/free.c			\
			srcs/ft_atoi.c		\
			srcs/ft_itoa.c		\
			srcs/init.c			\
			srcs/parsing.c		\
			srcs/philo_utils.c	\
			srcs/utils.c		\

NAME	= philo

CC		= gcc

RM		= rm -f

CFLAGS	= -I includes -Wall -Wextra -Werror

OBJS	= $(SRCS:.c=.o)

$(NAME):	$(OBJS)
			@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re