/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 16:19:09 by memartin          #+#    #+#             */
/*   Updated: 2020/06/17 19:05:38 by memartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		delete_arg_export(void *element)
{
	char	*s;

	s = (char *)element;
	ft_strdel(&s);
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

static void		add_new_var_to_env(t_minishell *data, char *arg, int i)
{
	t_list		*new;
	t_var		*var;

	if (!(var = (t_var*)malloc(sizeof(t_var))))
		exit_error(data);
	var->key = ft_substr(arg, 0, i);
	var->value = ft_substr(arg, i + 1, ft_strlen(arg) - i - 1);
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

	(void)data;
	lst_arg = NULL;
	if (is_export_arg_empty(arg))
	{
		ft_printf("export empty -> print env without binaray and in order?\n");
		return ;
	}
	split_arg(&lst_arg, arg);
	if (!check_arg(lst_arg))
	{
		ft_printf("bad arguments\n");
		return ;
	}
	add_to_env(data, lst_arg);
	ft_lstclear(&lst_arg, &delete_arg_export);
}
