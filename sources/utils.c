/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 14:03:17 by memartin          #+#    #+#             */
/*   Updated: 2020/07/15 19:24:15 by user42           ###   ########.fr       */
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
	if (c == ' '|| c == '\t')
		return (1);
	return (0);
}
