/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 11:03:34 by lafontai          #+#    #+#             */
/*   Updated: 2020/06/22 18:00:35 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// creation d'un nouveau process pour chaque commande à exécuter
	// si séparateur est pipe on fait la redirection avec un processus enfant
	// si pas un pipe on exécute et on ferme le processus
// à la fin d'une suite de pipes on envoit stdout du dernier enfant sur stdout de minishell

void	line_iteration(t_minishell *data)
{
	t_list		*element;
	int			p_fd[2];

	element = data->cmd;
	while (element)
	{
		if (pipe(p_fd))
			return ;
		create_process(data, element, p_fd, NULL);
		close(p_fd[0]);
		close(p_fd[1]);
		// check for redirections
		while (((t_command *)element->content)->separator == PIPE)
			element = element->next;
		element = element->next;
	}
}

void	execute_child(t_minishell *data, t_command *cmd, t_list *element)
{
	(void)element;
	ft_printf("Child PID is %d\n", getpid());
	command_router(data, cmd);
	exit(0);
}

void	execute_parent(t_minishell *data, t_list *element, pid_t cpid, int p_fd[2])
{
	int			status;
	int			c_fd[2];
	t_command	*cmd;

	if (pipe(c_fd) < 0)
		return ;
	cmd = (t_command *)element->content;
	if (cmd->separator == PIPE)
	{
		create_process(data, element->next, p_fd, c_fd);
	}
	close_fds(p_fd, c_fd);
	if (waitpid(cpid, &status, WUNTRACED | WCONTINUED) == -1)
		exit_error(data);
	if (WIFEXITED(status))
		ft_printf("Exited child %d\n", (int)cpid);
}

void	create_process(t_minishell *data, t_list *element, int p_fd[2], int c_fd[2])
{
	pid_t		cpid;
	t_command	*cmd;
	char		*str;

	cmd = (t_command *)element->content;
	replace_variables(data, cmd);
	str = ft_strtrim(cmd->cmd, " ");
	if (!ft_strncmp(str, "exit ", 5) || !ft_strcmp(str, "exit"))
	{
		ft_strdel(&str);
		exit_normal(data);
	}
	if ((cpid = fork()) == -1)
	{
		ft_printf("%s\n", strerror(errno));
		exit_error(data);
	}
	if (cpid == 0)
	{
		handle_fd(cmd, p_fd, c_fd);
		execute_child(data, cmd, element);
	}
	else
	{
		execute_parent(data, element, cpid, p_fd);
	}
	//while (!WIFEXITED(status) && !WIFSIGNALED(status))
    //	exit_normal(data);
}
