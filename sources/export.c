/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 16:19:09 by memartin          #+#    #+#             */
/*   Updated: 2020/06/19 11:59:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		check_arg(t_list *lst_arg)
{
	char		*s;

	while (lst_arg)
	{
		s = (char*)lst_arg->content;
		if (!ft_isalpha(*s++))
			return (0);
		while (*s && (ft_isalnum(*s) || *s == '_'))
			s++;
		if (*s++ != '=')
			return (0);
		while (*s && is_export_char(*s))
			s++;
		if (*s)
			return (0);
		lst_arg = lst_arg->next;
	}
	return (1);
}

static int		is_key_exist(t_minishell *data, char *key, char *value)
{
	t_var	*var;
	t_list	*element;

	element = data->env;
	while (element)
	{
		var = (t_var*)element->content;
		if (!ft_strcmp(key, var->key))
		{
			ft_strdel(&var->value);
			var->value = value;
			ft_strdel(&key);
			return (1);
		}
		element = element->next;
	}
	return (0);
}

static void		add_new_var_to_env(t_minishell *data, char *arg, int i)
{
	t_list		*new;
	t_var		*var;
	char		*key;
	char		*value;

	key = ft_substr(arg, 0, i);
	value = ft_substr(arg, i + 1, ft_strlen(arg) - i - 1);
	if (is_key_exist(data, key, value))
		return ;
	if (!(var = (t_var*)malloc(sizeof(t_var))))
		exit_error(data);
	var->key = key;
	var->value = value;
	var->local = 0;
	new = ft_lstnew((void*)var);
	ft_lstadd_back(&data->env, new);
}

static void		add_to_env(t_minishell *data, t_list *lst_arg)
{
	char	*arg;
	int		i;

	while (lst_arg)
	{
		i = 0;
		arg = (char*)lst_arg->content;
		while (arg[i] && arg[i] != '=')
			i++;
		add_new_var_to_env(data, arg, i);
		lst_arg = lst_arg->next;
	}
}

void			ft_export(t_minishell *data, char *arg)
{
	t_list		*lst_arg;
	t_list		*tmp_env;

	(void)data;
	lst_arg = NULL;
	if (is_export_arg_empty(arg))
	{
		tmp_env = duplicate_env(data);
		ft_lstiter(tmp_env, &print_export_empty);
		ft_lstclear(&tmp_env, &del_variable);
		return ;
	}
	split_arg(&lst_arg, arg);
	if (!check_arg(lst_arg))
	{
		ft_printf("bad arguments\n");
		ft_lstclear(&lst_arg, &delete_arg);
		return ;
	}
	add_to_env(data, lst_arg);
	ft_lstclear(&lst_arg, &delete_arg);
}
