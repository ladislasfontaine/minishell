/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 12:06:33 by memartin          #+#    #+#             */
/*   Updated: 2020/06/17 12:40:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		print_env(void *element)
{
	t_var		*var;

	var = (t_var*)element;
	if (!var->local)
		ft_printf("%s=%s\n", var->key, var->value);
}

void			env(t_minishell *data)
{
	ft_lstiter(data->env, &print_env);
}
