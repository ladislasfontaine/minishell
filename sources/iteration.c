/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iteration.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 19:02:13 by lafontai          #+#    #+#             */
/*   Updated: 2020/06/17 14:47:12 by memartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		command_router(t_minishell *data, t_command *command)
{
	// enlever les espaces
	// attention à pwdd par exemple
	if (ft_strncmp(command->cmd, "exit", 4) == 0)
	{
		reset_command(data);
		exit(0);
	}
	else if (ft_strncmp(command->cmd, "pwd", 3) == 0)
		print_cwd();
	else if (ft_strncmp(command->cmd, "cd ", 3) == 0)
		change_directory(command->cmd + 3);
	else if (!ft_strncmp(command->cmd, "env", 3))
		env(data);
	else if (!ft_strncmp(command->cmd, "unset ", 6))
		unset(data, command->cmd + 6);
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
