# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/15 15:08:42 by lafontai          #+#    #+#              #
#    Updated: 2020/06/17 09:08:28 by lafontai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= $(addprefix $(FOLDER), \
			minishell.c \
			init.c \
			iteration.c \
			parser.c \
			cd.c \
			pwd.c \
			)

OBJS	= $(SRCS:.c=.o)

FOLDER	= sources/

INCS	= includes/

INC_LIB	= libft/includes/

NAME	= minishell

RM		= rm -f

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror

ifeq ($(DEBUG), true)
	CFLAGS += -g -fsanitize=address
endif

all:		$(NAME)

$(NAME):	$(OBJS)
			cd libft/ && make
			$(CC) $(CFLAGS) libft/libft.a $(OBJS) -o $(NAME)

%.o:		%.c
			$(CC) $(CFLAGS) -c $< -o $@ -I $(INCS) -I $(INC_LIB)

clean:
			make clean -C libft/
			$(RM) $(OBJS)

fclean:		clean
			$(RM) libft/libft.a
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
