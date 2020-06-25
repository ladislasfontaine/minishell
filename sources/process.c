/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 11:03:34 by lafontai          #+#    #+#             */
/*   Updated: 2020/06/25 14:26:39 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	line_iteration(t_minishell *data)
{
	t_list		*element;
	t_command	*cmd;
	int			p_fd[2];

	element = data->cmd;
	while (element)
	{
		cmd = (t_command *)element->content;
		if (pipe(p_fd))
			return ;
		if (!command_router_no_process(data, cmd))
			create_process(data, element, p_fd, NULL);
		close(p_fd[0]);
		close(p_fd[1]);
		while (cmd->separator == PIPE && element)
		{
			element = element->next;
			cmd = (t_command *)element->content;
		}
		element = element->next;
	}
}

void	execute_child(t_minishell *data, t_command *cmd, t_list *element)
{
	char	*tmp;

	(void)element;
	tmp = cmd->cmd;
	//ft_printf("Child PID is %d\n", getpid());
	cmd->cmd = ft_strtrim(tmp, " ");
	if (cmd->cmd)
	{
		if (!command_router_no_process(data, cmd))
			command_router(data, cmd);
	}
	free(tmp);
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
	//if (WIFEXITED(status))
	//	ft_printf("Exited child %d\n", (int)cpid);
}

void	create_process(t_minishell *data, t_list *element, int p_fd[2], int c_fd[2])
{
	pid_t		cpid;
	t_command	*cmd;
	char		*str;

	cmd = (t_command *)element->content;
	str = ft_strtrim(cmd->cmd, " ");
	(void)str;
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
		if (cmd->separator == PIPE && cmd->previous && cmd->previous->separator == PIPE
			&& !(close(p_fd[0])) && !(close(p_fd[1])))
			execute_parent(data, element, cpid, c_fd);
		else
			execute_parent(data, element, cpid, p_fd);
	}
	//while (!WIFEXITED(status) && !WIFSIGNALED(status))
    //	exit_normal(data);
}
