/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 16:09:21 by lafontai          #+#    #+#             */
/*   Updated: 2020/06/18 08:57:53 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_minishell(t_minishell *data)
{
	data->line = NULL;
	data->env = NULL;
	data->cmd = NULL;
	data->run = 1;
	data->separator = 0;
	data->s_quote = 0;
	data->d_quote = 0;
}

int		init_command(t_command **command, int sep, char *sub)
{
	if (!(*command = (t_command *)malloc(sizeof(t_command))))
		return (-1);
	if (!sub)
	{
		free(command);
		return (-1);
	}
	(*command)->cmd = sub;
	(*command)->separator = sep;
	(*command)->s_quote = 0;
	(*command)->d_quote = 0;
	(*command)->chevron = 0;
	return (0);
}

void	reset_command(t_minishell *data)
{
	if (data->line)
		free(data->line);
	data->line = NULL;
	ft_lstclear(&data->cmd, &del_command);
	data->cmd = NULL;
	data->s_quote = 0;
	data->d_quote = 0;
}
