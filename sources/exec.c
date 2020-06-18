/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 11:24:35 by lafontai          #+#    #+#             */
/*   Updated: 2020/06/18 20:05:02 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// faire une fonction strjoin_with(char *s1, char *s2, char with)
// free ce qu'il faut

char	**command_into_arguments(t_minishell *data, char *cmd)
{
	// faire un split qui prend en compte les quotes
	(void)data;
	return (ft_split(cmd, ' '));
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

void	fork_and_execute(t_minishell *data, char **argv, char *path)
{
	pid_t	cpid;
	pid_t	w;
	int		status;
	char	**envp;

	envp = create_env_tab(data);
	cpid = fork();
	if (cpid == -1)
        exit_error(data);
	if (cpid == 0)
	{/* Code executed by child */
		ft_printf("Child PID is %d\n", getpid());
		if (execve(path, argv, envp) == -1)
		{
			ft_printf("%s\n", strerror(errno));
			exit(1);
		}
	}
	else
	{/* Code executed by parent */
		if ((w = waitpid(cpid, &status, WUNTRACED | WCONTINUED)) == -1)
			exit_error(data);
	}
	while (!WIFEXITED(status) && !WIFSIGNALED(status))
    	exit_normal(data);
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
		ft_printf("Error message, No path var\n");
		return (-1);
	}
	// free les ft_split
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
			return (0);
		}
		else
			free(temp);
		i++;
	}
	return (-1);
}

void	command_execute(t_minishell *data, t_command *cmd)
{
	char	**argv;
	char	*path;

	argv = NULL;
	path = NULL;
	if (!(argv = command_into_arguments(data, cmd->cmd)))
		exit_error(data);
	if (!*argv)
		return ;
	else if (argv[0][0] == '/')
	{
		// absolute_path()
		path = ft_strdup(argv[0]);
		free(argv[0]);
		argv[0] = ft_strdup(ft_strrchr(path, '/'));
	}
	else
	{
		if (search_exec_in_path(data, argv, &path) == -1)
			return ;
	}
	fork_and_execute(data, argv, path);
}