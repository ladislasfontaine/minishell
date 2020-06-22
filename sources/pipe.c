/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 15:43:13 by lafontai          #+#    #+#             */
/*   Updated: 2020/06/22 18:26:29 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_fd(t_command *cmd, int p_fd[2], int c_fd[2])
{
	(void)c_fd;
	if (cmd->previous && cmd->previous->separator == PIPE)
	{
		dup2(p_fd[0], 0);
		close(p_fd[1]);
		if (cmd->separator == PIPE)
		{
			dup2(c_fd[1], 1);
			close(c_fd[0]);
		}
	}
	else if (cmd->separator == PIPE)
	{
		dup2(p_fd[1], 1);
		close(p_fd[0]);
	}
}

void	close_fds(int p_fd[2], int c_fd[2])
{
	close(p_fd[0]);
	close(p_fd[1]);
	close(c_fd[0]);
	close(c_fd[1]);
}

