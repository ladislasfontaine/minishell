# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/15 15:08:42 by lafontai          #+#    #+#              #
#    Updated: 2020/07/16 21:56:12 by lafontai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= $(addprefix $(FOLDER), \
			minishell.c \
			init.c \
			iteration.c \
			parser.c \
			variable.c \
			exec.c \
			exec_norm.c \
			process.c \
			pipe.c \
			redirect.c \
			echo.c \
			env.c \
			cd.c \
			pwd.c \
			exit.c \
			unset.c \
			utils.c \
			export.c \
			export_unset_utils.c \
			lst_utils.c \
			signal.c \
			print_error.c \
			print_error2.c \
			parse_synthax.c \
			delete.c \
			execute_child_parent.c \
			split_redirection.c \
			split_special.c \
			split_utils.c \
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
			@cd libft/ && make
			@$(CC) $(CFLAGS) $(OBJS) -L./libft -lft -o $(NAME)

%.o:		%.c
			@$(CC) $(CFLAGS) -I $(INCS) -I $(INC_LIB) -c $< -o $@ 

clean:
			@make clean -C libft/
			@$(RM) $(OBJS)

fclean:		clean
			@$(RM) libft/libft.a
			@$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
