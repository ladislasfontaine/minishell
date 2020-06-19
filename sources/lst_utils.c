/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 11:32:02 by memartin          #+#    #+#             */
/*   Updated: 2020/06/19 12:10:05 by memartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			add_new_var_dup(t_list **tmp_env, t_var *var)
{
	t_var 	*new_var;
	t_list	*new;

	if (!(new_var = (t_var*)malloc(sizeof(t_var))))
		return (0);
	new_var->key = ft_strdup(var->key);
	new_var->value = ft_strdup(var->value);
	new_var->local = var->local;
	new = ft_lstnew((void*)new_var);
	ft_lstadd_back(tmp_env, new);
	return (1);
}

static t_list	*sort_env(t_list *tmp_env)
{
	t_list	*start;
	t_var	*var1;
	t_var	*var2;
	void	*swap;
	int		size;

	size = ft_lstsize(tmp_env);
	start = tmp_env;
	while (size--)
	{
		tmp_env = start;
		while (tmp_env->next)
		{
			var1 = (t_var*)tmp_env->content;
			var2 = (t_var*)tmp_env->next->content;
			if (ft_strcmp(var1->key, var2->key) > 0)
			{
				swap = tmp_env->content;
				tmp_env->content = tmp_env->next->content;
				tmp_env->next->content = swap;
			}
			tmp_env = tmp_env->next;
		}
	}
	return (start);
}


t_list			*duplicate_env(t_minishell *data)
{
	t_list		*tmp_env;
	t_list		*env;
	
	tmp_env = NULL;
	env = data->env;
	while (env)
	{
		if (!add_new_var_dup(&tmp_env, (t_var*)env->content))
		{
			ft_lstclear(&tmp_env, &del_variable);
			exit_error(data);
		}
		env = env->next;
	}
	tmp_env = sort_env(tmp_env);
	return (tmp_env);
}
