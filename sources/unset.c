/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 12:38:59 by memartin          #+#    #+#             */
/*   Updated: 2020/06/17 19:13:03 by memartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		delete_arg_unset(void *element)
{
	char	*s;

	s = (char *)element;
	ft_strdel(&s);
}

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
			{
				ft_lstdelone(element->next, &delete_one_env);
				element->next = NULL;
			}
		}
		element = element->next;
	}
}

static void		create_new_arg(t_list **lst_arg, char *arg, int start, int end)
{
	t_list		*new;
	int			len;

	len = (end - start) < 0 ? 0 : (end - start);
	new = ft_lstnew((void*)ft_substr(arg, start, len));
	ft_lstadd_back(lst_arg, new);
}

static void		split_arg(t_list **lst_arg, char *arg)
{
	int			i;
	int			old_i;

	i = 0;
	old_i = 0;
	while (arg[i])
	{
		while (arg[i] && is_whitespace(arg[i]))
			i++;
		old_i = i;
		while (arg[i] && !is_whitespace(arg[i]))
			i++;
		if (old_i != i)
			create_new_arg(lst_arg, arg, old_i, i);
	}
}

void			unset(t_minishell *data, char *arg)
{
	t_list		*lst_arg;
	t_list		*tmp;
	t_var		*var;

	if (!*arg)
	{
		ft_printf("unset: not enough arguments\n");
		return ;
	}
	lst_arg = NULL;
	split_arg(&lst_arg, arg);
	while (lst_arg)
	{
		var = (t_var *)data->env;
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
	ft_lstclear(&lst_arg, &delete_arg_unset);
}
