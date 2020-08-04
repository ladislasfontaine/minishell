/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 13:02:48 by memartin          #+#    #+#             */
/*   Updated: 2020/08/04 16:30:33 by memartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_key_exist_check
	(t_minishell *data, char *key)
{
	t_var	*var;
	t_list	*element;

	element = data->env;
	while (element)
	{
		var = (t_var*)element->content;
		if (!ft_strcmp(key, var->key))
			return (1);
		element = element->next;
	}
	return (0);
}

void		print_export_empty(void *element)
{
	t_var		*var;

	var = (t_var *)element;
	if (var->key[0] == '_' && var->key[1] == '\0')
		return ;
	ft_printf("declare -x %s=\"%s\"\n", var->key, var->value);
}
