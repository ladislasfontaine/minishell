/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 11:24:35 by lafontai          #+#    #+#             */
/*   Updated: 2020/07/16 10:18:14 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **tab)
{
	int	i;

	if (tab)
	{
		i = 0;
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}

char	**create_env_tab(t_minishell *data)
{
	t_list	*element;
	t_var	*var;
	char	**tab;
	int		size;
	int		i;

	// attention juste les variables dans env
	size = ft_lstsize(data->env);
	tab = (char **)malloc(sizeof(char *) * (size + 1));
	element = data->env;
	i = 0;
	while (i < size)
	{
		var = (t_var *)element->content;
		tab[i] = ft_strjoin_with(var->key, var->value, '=');
		i++;
		element = element->next;
	}
	tab[i] = 0;
	return (tab);
}

void	execute_binary(t_minishell *data, char **argv, char *path)
{
	char	**envp;
	pid_t	cpid;
	int		status;

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
	{
		free_tab(envp);
		if (waitpid(cpid, &status, WUNTRACED | WCONTINUED) == -1)
			exit_error(data);
		if (WIFEXITED(status))
			data->exit = WEXITSTATUS(status);
	}
}

int		search_exec_in_path(t_minishell *data, char **argv, char **path)
{
	char		**path_tab;
	char		*temp;
	int			i;
	struct stat	sb;

	if (!(*path = get_var_value(data, "PATH")))
		exit_error(data);
	if (**path == '\0')
	{
		ft_putstr_fd("Error message, No path var\n", 2);
		return (-1);
	}
	path_tab = ft_split(*path, ':');
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

void	command_execute(t_minishell *data, t_command *cmd)
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
	// attention à modifier cmd->args pour gérer le cas avec une path absolu
	// si pas besoin virer argv
	execute_binary(data, cmd->args, path);
	free_tab(argv);
}
