/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 09:49:07 by lafontai          #+#    #+#             */
/*   Updated: 2020/07/15 18:27:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
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
#define GREEN "\033[1;32m"
#define CYAN "\033[1;36m"
#define RESET "\033[0m"

typedef struct	s_var
{
	char	*key;
	char	*value;
	int		local;
}				t_var;

typedef struct	s_command
{
	char				*cmd;
	char				**args;
	int					separator;
	int					s_quote;
	int					d_quote;
	int					chevron;
	int					in;
	int					out;
	int					fd[2];
	struct s_command	*previous;
}				t_command;

typedef struct	s_minishell
{
	char	*line;
	t_list	*env;
	t_list	*cmd;
	int		run;
	int		signal_set;
	int		separator;
	int		s_quote;
	int		d_quote;
	int		stop;
	int		exit;
}				t_minishell;

void	init_minishell(t_minishell *data);
int		init_command(t_command **command, int sep, char *sub, t_list *previous);
void	del_command(void *element);
void	del_variable(void *element);
void	clear_all(t_minishell *data);
void	reset_command(t_minishell *data);
void	line_iteration(t_minishell *data);
void	command_router(t_minishell *data, t_command *command);
int		command_router_no_process(t_minishell *data, t_command *command);
int		redirection_router(t_minishell *data, t_command *cmd);
char	*remove_spaces(char *str);
char	*dup_first_word(char *str);
void	replace_variables(t_minishell *data, t_command *cmd);
int		create_command(t_minishell *data, int start, int end);
void	free_tab(char **tab);

int		split_line(t_minishell *data);
void	split_command(t_command *cmd);
int		process_command(t_minishell *data, t_list *element);
int		check_pipe_semi_collon(t_minishell *data);
int		parse_chevron(t_minishell *data, char *arg1, char *arg2);
int		check_first_chevron(t_minishell *data, char *arg);
t_list	*duplicate_env(t_minishell *data);
void	print_export_empty(void *element);

void	print_error_cmd_not_found(char *s);
void	print_error_parse_near(char *s1);
void	print_error_exec_errno(char *s1, char *s2);

void	command_execute(t_minishell *data, t_command *cmd);
char	*get_var_value(t_minishell *data, char *key);
void	check_quotes(char letter, int *s_quote, int *d_quote);
void	create_process(t_minishell *data, t_list *element, int p_fd[2], int c_fd[2]);
void	handle_fd(t_command *cmd, int p_fd[2], int c_fd[2]);
void	close_fds(int p_fd[2], int c_fd[2]);
/* ECHO */
void	command_echo(t_minishell *data, t_command *cmd);
/* CD */
int		command_cd(t_minishell *data, t_command *cmd);
/* PWD */
int		command_pwd(t_minishell *data, t_command *cmd);
char	*return_cwd(void);
/* EXPORT */
void	ft_export(t_minishell *data, char **arg);
/* UNSET */
void	unset(t_minishell *data, char **arg);
/* ENV */
void	init_env(t_minishell *data, char **env);
void	env(t_minishell *data);
/* EXIT */
void	command_exit(t_minishell *data, t_command *cmd);
void	exit_normal(t_minishell *data);
void	exit_error(t_minishell *data);
/* SIGNAL */
void	(*SIGINT_handler)(int);
void	(*SIGQUIT_handler)(int);
void	ignore_signal(t_minishell *data);
void	restore_signals_in_child(t_minishell *data);

int		is_export_arg_empty(char *arg);
int		is_export_char(char c);
int		is_whitespace(char c);
#endif
