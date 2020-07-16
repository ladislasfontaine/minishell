/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 11:24:35 by lafontai          #+#    #+#             */
/*   Updated: 2020/07/16 14:53:40 by memartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		execute_binary_next
	(t_minishell *data, char **envp, pid_t cpid)
{
	int		status;

	free_tab(envp);
	if (waitpid(cpid, &status, WUNTRACED | WCONTINUED) == -1)
		exit_error(data);
	if (WIFEXITED(status))
		data->exit = WEXITSTATUS(status);
}

void			execute_binary(t_minishell *data, char **argv, char *path)
{
	char	**envp;
	pid_t	cpid;

	envp = create_env_tab(data);
	if ((cpid = fork()) == -1)
	{
		ft_printf("%s\n", strerror(errno));
		free_tab(envp);
		exit_error(data);
	}
	if (cpid == 0)
	{
		if (execve(path, argv, envp) == -1)
		{
			print_error_exec_errno(argv[0], strerror(errno));
			data->exit = 1;
			free_tab(envp);
			exit(1);
		}
		free_tab(envp);
	}
	else
		execute_binary_next(data, envp, cpid);
}

static int		search_exec_in_path_next
	(t_minishell *data, char **argv, char **path, char **path_tab)
{
	char			*temp;
	int				i;
	struct stat		sb;

	i = 0;
	while (path_tab[i])
	{
		temp = ft_strjoin_with(path_tab[i], argv[0], '/');
		if (stat(temp, &sb) == 0)
		{
			free(*path);
			*path = ft_strdup(temp);
			free(temp);
			free_tab(path_tab);
			return (0);
		}
		else
			free(temp);
		i++;
	}
	free_tab(path_tab);
	print_error_cmd_not_found(data, argv[0]);
	return (-1);
}

int				search_exec_in_path(t_minishell *data, char **argv, char **path)
{
	char		**path_tab;

	if (!(*path = get_var_value(data, "PATH")))
		exit_error(data);
	if (**path == '\0')
	{
		ft_putstr_fd("Error message, No path var\n", 2);
		return (-1);
	}
	path_tab = ft_split(*path, ':');
	if (search_exec_in_path_next(data, argv, path, path_tab) == 0)
		return (0);
	else
		return (-1);
}

void			command_execute(t_minishell *data, t_command *cmd)
{
	char	**argv;
	char	*path;

	argv = NULL;
	path = NULL;
	if (!(argv = ft_split_special(cmd->cmd, ' ')))
		exit_error(data);
	if (!*argv)
		return ;
	else if (argv[0][0] == '/')
	{
		path = ft_strdup(argv[0]);
		free(argv[0]);
		argv[0] = ft_strdup(ft_strrchr(path, '/'));
	}
	else
	{
		if (search_exec_in_path(data, argv, &path) == -1)
			return ;
	}
	execute_binary(data, cmd->args, path);
	free_tab(argv);
}
