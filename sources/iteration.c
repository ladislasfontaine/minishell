/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iteration.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 19:02:13 by lafontai          #+#    #+#             */
/*   Updated: 2020/06/25 15:23:20 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_router(t_minishell *data, t_command *command)
{
	char	*cmd;

	cmd = ft_strtrim(command->cmd, " ");
	if (!ft_strncmp(cmd, "pwd ", 4) || !ft_strcmp(cmd, "pwd"))
		print_cwd();
	else if (!ft_strncmp(cmd, "echo ", 5) || !ft_strcmp(cmd, "echo"))
		command_echo(data, command, cmd + 4);
	else if (!ft_strncmp(cmd, "env ", 4) || !ft_strcmp(cmd, "env"))
		env(data);
	else if	(!ft_strcmp(cmd, "export"))
		ft_export(data, cmd + 6);
	else
		command_execute(data, command);
	exit(0);
}

int		command_router_no_process(t_minishell *data, t_command *command)
{
	char	*cmd;

	cmd = ft_strtrim(command->cmd, " ");
	if (ft_strncmp(cmd, "cd ", 3) == 0 && command->separator != PIPE)
		change_directory(cmd + 3);
	else if (!ft_strncmp(cmd, "unset ", 6) && command->separator != PIPE)
		unset(data, cmd + 6);
	else if	(!ft_strncmp(cmd, "export ", 7) && command->separator != PIPE)
		ft_export(data, cmd + 6);
	else if ((!ft_strncmp(cmd, "exit ", 5) || !ft_strcmp(cmd, "exit")) && command->separator != PIPE)
		exit_normal(data);
	else
		return (0);
	return (1);
}
