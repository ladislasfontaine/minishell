/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 09:49:07 by lafontai          #+#    #+#             */
/*   Updated: 2020/06/19 15:55:18 by lafontai         ###   ########.fr       */
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
void	del_variable(void *element);
void	clear_all(t_minishell *data);
void	reset_command(t_minishell *data);
void	line_iteration(t_minishell *data);
int		command_router(t_minishell *data, t_command *command);
char	*remove_spaces(char *str);
char	*dup_first_word(char *str);
void	replace_variables(t_minishell *data, t_command *cmd);
void	delete_arg(void *element);
void	create_new_arg(t_list **lst_arg, char *arg, int start, int end);
void	split_arg(t_list **lst_arg, char *arg);
t_list	*duplicate_env(t_minishell *data);
void	print_export_empty(void *element);


void	command_execute(t_minishell *data, t_command *cmd);
char	*get_var_value(t_minishell *data, char *key);
void	check_quotes(char letter, int *s_quote, int *d_quote);
void	create_process(t_minishell *data, t_list *element);
/* ECHO */
void	 command_echo(t_minishell *data, t_command *cmd, char *str);
/* CD */
int		change_directory(char *path);
/* PWD */
int		print_cwd(void);
/* EXPORT */
void	ft_export(t_minishell *data, char *cmd);
/* UNSET */
/* ENV */
void	init_env(t_minishell *data, char **env);
void	unset(t_minishell *data, char *arg);
void	env(t_minishell *data);
/* EXIT */
void	exit_normal(t_minishell *data);
void	exit_error(t_minishell *data);

int		is_export_arg_empty(char *arg);
int		is_export_char(char c);
int		is_whitespace(char c);
#endif
