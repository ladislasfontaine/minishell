/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iteration.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 19:02:13 by lafontai          #+#    #+#             */
/*   Updated: 2020/06/17 09:49:48 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		command_router(t_minishell *data, t_command *command)
{
	char	*cmd;

	cmd = ft_strtrim(command->cmd, " ");
	if (!ft_strncmp(cmd, "exit ", 5) || !ft_strcmp(cmd, "exit"))
	{
		reset_command(data);
		exit(0);
	}
	else if (!ft_strncmp(cmd, "pwd ", 4) || !ft_strcmp(cmd, "pwd"))
		print_cwd();
	else if (ft_strncmp(cmd, "cd ", 3) == 0)
		change_directory(cmd + 3);
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
		// replace_variables(command); // to replace $
		// command_parser(command); // to check for quotes, redirection 
		command_router(data, command);
		element = element->next;
	}
}
