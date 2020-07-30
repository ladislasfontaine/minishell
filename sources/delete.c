/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 15:20:54 by memartin          #+#    #+#             */
/*   Updated: 2020/07/30 16:06:26 by memartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_command(void *element)
{
	t_command	*temp;

	temp = (t_command *)element;
	if (temp->args)
		free_tab(temp->args);
	if (temp->was_in_quote)
		free(temp->was_in_quote);
	if (temp->cmd)
		free(temp->cmd);
	if (temp)
		free(temp);
}

void	del_variable(void *element)
{
	t_var	*temp;

	temp = (t_var *)element;
	if (temp->key)
		free(temp->key);
	if (temp->value)
		free(temp->value);
	if (temp)
		free(temp);
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
