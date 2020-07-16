/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 21:57:01 by lafontai          #+#    #+#             */
/*   Updated: 2020/07/16 22:33:59 by lafontai         ###   ########.fr       */
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

int		check_escape(const char *str, int i, int *esc)
{
	*esc = (str[i] == '\\' && !*esc) ? 1 : 0;
	return (*esc);
}
