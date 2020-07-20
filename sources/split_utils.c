/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 21:57:01 by lafontai          #+#    #+#             */
/*   Updated: 2020/07/20 16:55:10 by memartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_split(t_split *split)
{
	split->tab = NULL;
	split->i = 0;
	split->j = 0;
	split->k = 0;
	split->s_quote = 0;
	split->d_quote = 0;
	split->count = 0;
}

char	*replace_action_1(t_minishell *data, t_var var)
{
	if (g_signum == SIGINT)
		data->exit = 130;
	if (!(var.value = ft_itoa(data->exit)))
		free_exit_error(data, var.key);
	g_signum = 0;
	return (var.value);
}

int		check_escape(const char *str, int i, int *esc)
{
	*esc = (str[i] == '\\' && !*esc) ? 1 : 0;
	return (*esc);
}
