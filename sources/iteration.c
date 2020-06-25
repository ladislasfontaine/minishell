/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iteration.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 19:02:13 by lafontai          #+#    #+#             */
/*   Updated: 2020/06/25 16:18:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_router(t_minishell *data, t_command *command)
{
	char	*cmd;

	cmd = command->args[0];
	if (!ft_strcmp(cmd, "pwd"))
		print_cwd();
	else if (!ft_strcmp(cmd, "echo"))
		command_echo(command);
	else if (!ft_strcmp(cmd, "env"))
		env(data);
	else if	(!ft_strcmp(cmd, "export"))
		ft_export(data, command->args);
	else
		command_execute(data, command);
	exit(0);
}

int		command_router_no_process(t_minishell *data, t_command *command)
{
	char	*cmd;

	cmd = command->args[0];
	if (ft_strncmp(command->cmd, "cd ", 3) == 0 && command->separator != PIPE)
		change_directory(command->cmd + 3);
	else if (!ft_strcmp(cmd, "unset") && command->separator != PIPE)
		unset(data, command->args);
	else if	(!ft_strcmp(cmd, "export") && command->args[1] &&
		command->separator != PIPE)
		ft_export(data, command->args);
	else if (!ft_strcmp(cmd, "exit") && command->separator != PIPE)
		exit_normal(data);
	else
		return (0);
	return (1);
}
