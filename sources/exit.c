/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 12:13:10 by lafontai          #+#    #+#             */
/*   Updated: 2020/06/23 14:07:27 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_command(void *element)
{
	t_command	*temp;

	temp = (t_command *)element;
	if (temp->args)
		free_tab(temp->args);
	if (temp->cmd)
		free(temp->cmd);
}

void	del_variable(void *element)
{
	t_var	*temp;

	temp = (t_var *)element;
	if (temp->key)
		free(temp->key);
	if (temp->value)
		free(temp->value);
}

void	clear_all(t_minishell *data)
{
	if (data)
	{
		if (data->line)
			free(data->line);
		data->line = NULL;
		ft_lstclear(&data->cmd, &del_command);
		ft_lstclear(&data->env, &del_variable);
		data->cmd = NULL;
		data->env = NULL;
	}
}

void	exit_error(t_minishell *data)
{
	clear_all(data);
	exit(1);
}

void	exit_normal(t_minishell *data)
{
	clear_all(data);
	ft_printf("exit\n");
	exit(0);
}
