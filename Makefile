# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/13 12:16:45 by rvan-aud          #+#    #+#              #
#    Updated: 2021/10/26 10:46:21 by rvan-aud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= 	main.c		\
			free.c		\
			ft_atoi.c	\
			ft_itoa.c	\
			parsing.c	\
			philo.c		\
			utils.c		\

NAME	= philo

CC		= gcc

RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror

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