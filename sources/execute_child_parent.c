/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_child_parent.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 16:20:48 by memartin          #+#    #+#             */
/*   Updated: 2020/07/20 16:44:00 by memartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_child
	(t_minishell *data, t_command *cmd, t_list *element)
{
	char	*tmp;

	(void)element;
	tmp = cmd->cmd;
	cmd->cmd = ft_strtrim(tmp, " ");
	if (cmd->cmd)
	{
		if (!command_router_no_process(data, cmd))
			command_router(data, cmd);
	}
	free(tmp);
	if (g_signum == SIGINT)
		exit(130);
	else if (g_signum == SIGQUIT)
		exit(131);
	else
		exit(data->exit);
}

void	execute_parent
	(t_minishell *data, t_list *element, pid_t cpid, int p_fd[2])
{
	int			status;
	int			last;
	int			c_fd[2];
	t_command	*cmd;

	last = 0;
	if (pipe(c_fd) < 0)
		return ;
	cmd = (t_command *)element->content;
	if (cmd->separator == PIPE)
	{
		g_process = 1;
		create_process(data, element->next, p_fd, c_fd);
	}
	else
		last = 1;
	close_fds(p_fd, c_fd);
	if (waitpid(cpid, &status, WUNTRACED | WCONTINUED) == -1)
		exit_error(data);
	if (WIFEXITED(status) && last)
		data->exit = WEXITSTATUS(status);
}
