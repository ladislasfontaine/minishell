/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 16:19:09 by memartin          #+#    #+#             */
/*   Updated: 2020/07/16 14:20:22 by memartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		check_arg(char *s)
{
	if (!ft_isalpha(*s) || s[0] == '=')
		return (0);
	s++;
	while (*s && (ft_isalnum(*s) || *s == '_'))
		s++;
	if (*s == '+')
		s++;
	if (*s != '=' && *s != '\0')
		return (0);
	s++;
	while (*s != '\0' && is_export_char(*s))
		s++;
	if (*s != '\0')
		return (0);
	return (1);
}

static int		is_key_exist
	(t_minishell *data, char *key, char *value, int plus)
{
	t_var	*var;
	t_list	*element;

	element = data->env;
	while (element)
	{
		var = (t_var*)element->content;
		if (!ft_strcmp(key, var->key))
		{
			if (plus)
				var->value = ft_joinfree(var->value, value);
			else
			{
				ft_strdel(&var->value);
				var->value = value;
			}
			ft_strdel(&key);
			return (1);
		}
		element = element->next;
	}
	return (0);
}

static void		add_new_var_to_env
	(t_minishell *data, char *arg, int i, int plus)
{
	t_list		*new;
	t_var		*var;
	char		*key;
	char		*value;

	key = ft_substr(arg, 0, i);
	value = ft_substr(arg, i + 1 + plus, ft_strlen(arg) - i - 1);
	if (is_key_exist(data, key, value, plus))
		return ;
	if (!(var = (t_var*)malloc(sizeof(t_var))))
		exit_error(data);
	var->key = key;
	var->value = value;
	var->local = 0;
	new = ft_lstnew((void*)var);
	ft_lstadd_back(&data->env, new);
}

static void		add_to_env(t_minishell *data, char **arg)
{
	int		i;
	int		j;
	int		plus;

	j = 1;
	while (arg[j])
	{
		i = 0;
		plus = 0;
		if (check_arg(arg[j]))
		{
			while (arg[j][i] && arg[j][i] != '=' && arg[j][i] != '+')
				i++;
			if (arg[j][i] == '+')
				plus = 1;
			add_new_var_to_env(data, arg[j], i, plus);
		}
		else
		{
			print_error_export_id(arg[j]);
			data->exit = 1;
		}
		j++;
	}
}

void			ft_export(t_minishell *data, char **arg)
{
	t_list		*tmp_env;

	data->exit = 0;
	if (!arg[1])
	{
		tmp_env = duplicate_env(data);
		ft_lstiter(tmp_env, &print_export_empty);
		ft_lstclear(&tmp_env, &del_variable);
		return ;
	}
	add_to_env(data, arg);
}
