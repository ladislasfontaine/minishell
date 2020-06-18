/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iteration.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 19:02:13 by lafontai          #+#    #+#             */
/*   Updated: 2020/06/18 20:17:49 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		command_router(t_minishell *data, t_command *command)
{
	char	*cmd;

	cmd = ft_strtrim(command->cmd, " ");
	if (!ft_strncmp(cmd, "exit ", 5) || !ft_strcmp(cmd, "exit"))
		exit_normal(data);
	else if (!ft_strncmp(cmd, "pwd ", 4) || !ft_strcmp(cmd, "pwd"))
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
	ft_strdel(&cmd);
	return (0);
}

void	line_iteration(t_minishell *data)
{
	t_list		*element;
	t_command	*command;

	element = data->cmd;
	while (element)
	{
		command = (t_command *)element->content;
		replace_variables(data, command);
		// command_parser(command); // to check for quotes, redirection 
		command_router(data, command);
		element = element->next;
	}
}
