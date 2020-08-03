/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 14:03:17 by memartin          #+#    #+#             */
/*   Updated: 2020/08/03 13:32:15 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_export_arg_empty(char *arg)
{
	while (*arg && is_whitespace(*arg))
		arg++;
	if (!*arg)
		return (1);
	return (0);
}

int			is_export_char(char c)
{
	if (ft_isalnum(c) || c == '#' || c == '.' || c == '/' || c == '_' ||
		c == '-' || c == '*' || c == ':' || c == '@' || c == '^' || c == '+' ||
		c == '+' || c == '%' || c == '?' || c == ',' || c == '=' || c == ' ')
		return (1);
	return (0);
}

int			is_whitespace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int			is_not_separator(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

void		write_backslash(char const *s, t_split *d)
{
	if (check_escape(s, d->i, &d->count))
	{
		d->tab[d->j][d->k] = '\\';
		d->k++;
	}
	d->i++;
}
