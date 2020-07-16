/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 11:03:34 by lafontai          #+#    #+#             */
/*   Updated: 2020/07/16 16:27:24 by memartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command	*get_last_command(t_list *element)
{
	t_command	*cmd;

	cmd = (t_command*)element->content;
	while (element->next)
	{
		cmd = (t_command*)element->content;
		if (cmd->separator == PIPE)
			element = element->next;
		else
			break ;
	}
	return (cmd);
}

static t_list		*line_iteration_1(t_list *element, t_command *cmd)
{
	while (element->next && cmd->separator == PIPE)
	{
		element = element->next;
		cmd = (t_command *)element->content;
	}
	if (element->next)
		element = element->next;
	else
		element = NULL;
	return (element);
}

static t_list		*line_iteration_2
	(t_minishell *data, t_list *element, t_command *cmd)
{
	int			p_fd[2];

	if (pipe(p_fd))
		return (element);
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
	return (element);
}

void				line_iteration(t_minishell *data)
{
	t_list		*element;
	t_command	*cmd;

	element = data->cmd;
	while (element)
	{
		cmd = (t_command *)element->content;
		if (!cmd->previous ||
			(cmd->previous && cmd->previous->separator == SEMI_COLON))
		{
			if (command_router_no_process(data, get_last_command(element)))
			{
				element = line_iteration_1(element, cmd);
				continue ;
			}
		}
		element = line_iteration_2(data, element, cmd);
	}
}

void				create_process
	(t_minishell *data, t_list *element, int p_fd[2], int c_fd[2])
{
	pid_t		cpid;
	t_command	*cmd;

	cmd = (t_command *)element->content;
	if ((cpid = fork()) == -1)
	{
		print_error_fork(strerror(errno));
		data->exit = 128;
		exit_error(data);
	}
	if (cpid == 0)
	{
		restore_signals_in_child(data);
		handle_fd(cmd, p_fd, c_fd);
		execute_child(data, cmd, element);
	}
	else
	{
		if (cmd->separator == PIPE && cmd->previous &&
			cmd->previous->separator == PIPE
			&& !(close(p_fd[0])) && !(close(p_fd[1])))
			execute_parent(data, element, cpid, c_fd);
		else
			execute_parent(data, element, cpid, p_fd);
	}
}
