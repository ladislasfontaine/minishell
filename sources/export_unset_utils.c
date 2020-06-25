/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 13:02:48 by memartin          #+#    #+#             */
/*   Updated: 2020/06/25 16:24:54 by user42           ###   ########.fr       */
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
