/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 12:38:59 by memartin          #+#    #+#             */
/*   Updated: 2020/06/19 12:17:45 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		delete_one_env(void	*element)
{
	t_var		*var;

	var = (t_var*)element;
	if (var->key)
		free(var->key);
	if (var->value)
		free(var->value);
}

static void		search_unset(t_minishell *data, char *target)
{
	t_list		*element;
	t_list		*tmp;
	t_var		*var;
	
	element = data->env;
	while (element->next)
	{
		var = (t_var*)element->next->content;
		if (!ft_strcmp(target, var->key))
		{
			if (element->next->next != NULL)
			{
				tmp = element->next->next;
				ft_lstdelone(element->next, &delete_one_env);
				element->next = tmp;
			}
			else
				ft_lstdelone(element->next, &delete_one_env);
		}
		element = element->next;
	}
}

void			unset(t_minishell *data, char *arg)
{
	t_list		*lst_arg;
	t_list		*tmp;
	t_var		*var;

	lst_arg = NULL;
	split_arg(&lst_arg, arg);
	while (lst_arg)
	{
		var = (t_var *)data->env->content;
		if (!ft_strcmp((char*)lst_arg->content, var->key))
		{
			tmp = data->env->next;
			ft_lstdelone(data->env, &delete_one_env);
			data->env = tmp;
		}
		else
			search_unset(data, (char*)lst_arg->content);
		lst_arg = lst_arg->next;
	}
	ft_lstclear(&lst_arg, &delete_arg);
}
