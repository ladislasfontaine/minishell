/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 09:49:07 by lafontai          #+#    #+#             */
/*   Updated: 2020/06/17 15:19:06 by memartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include "libft.h"
#include "printf.h"

#define CMD_SIZE 5121
#define NONE 0
#define SEMI_COLON 1
#define PIPE 2
#define RIGHT 1
#define LEFT 2
#define D_RIGHT 3

typedef struct	s_var
{
	char	*key;
	char	*value;
	int		local;
}				t_var;

typedef struct	s_command
{
	char	*cmd;
	int		separator;
	int		s_quote;
	int		d_quote;
	int		chevron;
}				t_command;

typedef struct	s_minishell
{
	char	*line;
	t_list	*env;
	t_list	*cmd;
	int		run;
	int		separator;
	int		s_quote;
	int		d_quote;
}				t_minishell;

void	init_minishell(t_minishell *data);
int		init_command(t_command **command, int sep, char *sub);
void	del_command(void *element);
void	reset_command(t_minishell *data);
void	line_iteration(t_minishell *data);
int		command_router(t_minishell *data, t_command *command);
/* ECHO */
/* CD */
int		change_directory(char *path);
/* PWD */
void	print_cwd(void);
/* EXPORT */
void	unset(t_minishell *data, char *arg);
void	env(t_minishell *data);
/* EXIT */


int		is_whitespace(char c);
#endif
