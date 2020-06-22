/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iteration.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 19:02:13 by lafontai          #+#    #+#             */
/*   Updated: 2020/06/22 15:39:21 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_router(t_minishell *data, t_command *command)
{
	char	*cmd;

	cmd = command->cmd;
	if (!ft_strncmp(cmd, "pwd ", 4) || !ft_strcmp(cmd, "pwd"))
		print_cwd();
	else if (ft_strncmp(cmd, "cd ", 3) == 0)
		change_directory(cmd + 3);
	else if (!ft_strncmp(cmd, "echo ", 5) || !ft_strcmp(cmd, "echo"))
		command_echo(data, command, cmd + 4);
	else if (!ft_strncmp(cmd, "env ", 4) || !ft_strcmp(cmd, "env"))
		env(data);
	else if (!ft_strncmp(cmd, "unset ", 6))
		unset(data, cmd + 6);
	else if	(!ft_strncmp(cmd, "export ", 7) || !ft_strcmp(cmd, "export"))
		ft_export(data, cmd + 6);
	else
		command_execute(data, command);
	exit(0);
}
