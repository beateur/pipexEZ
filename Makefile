# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bihattay <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/06 10:07:33 by bihattay          #+#    #+#              #
#    Updated: 2021/10/06 10:09:56 by bihattay         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				= gcc
RM				= rm -f
CFLAGS		= -Wall -Wextra -Werror
NAME			= pipex
SRCS			= free.c\
						paths.c\
						utils.c\
						ft_split.c\
						ft_strjoin.c\
						do_split.c\
						main.c

OBJS			= $(SRCS:.c=.o)

all:
		make $(NAME)

$(NAME):  $(OBJS)
		gcc ${CFLAGS} -o ${NAME} ${OBJS}

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY:			all clean fclean re
