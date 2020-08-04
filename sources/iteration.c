/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iteration.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 19:02:13 by lafontai          #+#    #+#             */
/*   Updated: 2020/08/04 17:16:42 by memartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_router(t_minishell *data, t_command *command)
{
	char	*cmd;
	
	if (!command->remove)
	{
		command->remove =1;
		remove_backslash(command->args, command);
	}
	cmd = command->args[0];
	if (!cmd)
		return ;
	if (!ft_strcmp(cmd, "pwd"))
		command_pwd(data, command);
	else if (!ft_strcmp(cmd, "echo"))
		command_echo(data, command);
	else if (!ft_strcmp(cmd, "env"))
		env(data);
	else if (!ft_strcmp(cmd, "export"))
		ft_export(data, command->args);
	else
		command_execute(data, command);
}

int		command_router_no_process(t_minishell *data, t_command *command)
{
	char	*cmd;

	if (!command->remove)
	{
		command->remove =1;
		remove_backslash(command->args, command);
	}
	cmd = command->args[0];
	if (!cmd)
		return (0);
	if (ft_strequ(command->args[0], "cd") && command->separator != PIPE)
		command_cd(data, command);
	else if (!ft_strcmp(cmd, "unset") && command->separator != PIPE)
		unset(data, command->args);
	else if (!ft_strcmp(cmd, "export") && command->args[1] &&
		command->separator != PIPE)
		ft_export(data, command->args);
	else if (!ft_strcmp(cmd, "exit") && command->separator != PIPE)
		command_exit(data, command);
	else
		return (0);
	return (1);
}
