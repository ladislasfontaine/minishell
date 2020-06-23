# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/23 09:39:28 by lafontai          #+#    #+#              #
#    Updated: 2020/06/23 13:34:13 by lafontai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= \
			ft_atoi.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_convert_base.c \
			ft_convert_base2.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_islower.c \
			ft_isprint.c \
			ft_isupper.c \
			ft_itoa_u.c \
			ft_itoa.c \
			ft_itohex.c \
			ft_memalloc.c \
			ft_memccpy.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memdel.c \
			ft_memmove.c \
			ft_memset.c \
			ft_numlen.c \
			ft_putchar_fd.c \
			ft_putchar.c \
			ft_putendl_fd.c \
			ft_putendl.c \
			ft_putnbr_fd.c \
			ft_putnbr.c \
			ft_putstr_fd.c \
			ft_putstr.c \
			ft_putstrn.c \
			ft_split.c \
			ft_split_special.c \
			ft_split_special_redir.c \
			ft_strcat.c \
			ft_strchr.c \
			ft_strclr.c \
			ft_strcmp.c \
			ft_strcpy.c \
			ft_strdel.c \
			ft_strdup.c \
			ft_strequ.c \
			ft_striter.c \
			ft_striteri.c \
			ft_strjoin.c \
			ft_strjoin_with.c \
			ft_joinfree.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strmapi.c \
			ft_strncat.c \
			ft_strncmp.c \
			ft_strncpy.c \
			ft_strnequ.c \
			ft_strnew.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strstr.c \
			ft_strtrim.c \
			ft_substr.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_ultohex.c \
			get_next_line.c \
			ft_lstadd_back.c \
			ft_lstadd_front.c \
			ft_lstclear.c \
			ft_lstdelone.c \
			ft_lstiter.c \
			ft_lstlast.c \
			ft_lstmap.c \
			ft_lstnew.c \
			ft_lstsize.c \
			printf/flag1.c \
			printf/flag2.c \
			printf/format1.c \
			printf/format2.c \
			printf/ft_printf.c \
			printf/list.c \
			printf/parse.c \
			printf/utils.c

OBJS	= $(SRCS:.c=.o)

INC		= includes/

NAME	= libft.a

RM		= rm -f

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror

ifeq ($(DEBUG), true)
	CFLAGS += -g -fsanitize=address
endif

all:		$(NAME)

$(NAME):	$(OBJS)
			@ar rcs $(NAME) $(OBJS)

%.o:		%.c
			@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC)

clean:
			@$(RM) $(OBJS)

fclean:		clean
			@$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus
