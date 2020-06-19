/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 13:02:48 by memartin          #+#    #+#             */
/*   Updated: 2020/06/19 12:11:46 by memartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		print_export_empty(void *element)
{
	t_var		*var;

	var = (t_var *)element;
	if (var->key[0] == '_' && var->key[1] == '\0')
		return ;
	ft_printf("declare -x %s=\"%s\"\n", var->key, var->value);
}

void		delete_arg(void *element)
{
	char	*s;

	s = (char *)element;
	ft_strdel(&s);
}

void		create_new_arg(t_list **lst_arg, char *arg, int start, int end)
{
	t_list		*new;
	int			len;

	len = (end - start) < 0 ? 0 : (end - start);
	new = ft_lstnew((void*)ft_substr(arg, start, len));
	ft_lstadd_back(lst_arg, new);
}

void		split_arg(t_list **lst_arg, char *arg)
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
