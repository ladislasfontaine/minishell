/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 08:00:35 by lafontai          #+#    #+#             */
/*   Updated: 2020/06/16 14:24:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

char	*flag_minus(t_arg *params, char *arg)
{
	int		i;
	int		diff;
	int		len;
	char	*new;

	len = params->length ? (unsigned int)params->length : ft_strlen(arg);
	diff = params->flag_minus - len;
	if (diff > 0)
	{
		i = len;
		new = ft_strnew(params->flag_minus);
		ft_strcpy(new, (const char *)arg);
		if (params->format == 'c' && arg[0] == '\0')
			new[0] = '\0';
		free(arg);
		while (i < params->flag_minus)
		{
			new[i] = ' ';
			i++;
		}
		if (params->format == 'c')
			params->length += diff;
		return (new);
	}
	return (arg);
}

char	*flag_width(t_arg *params, char *arg)
{
	int		i;
	int		flag;
	int		len;
	char	*new;

	len = params->length ? (unsigned int)params->length : ft_strlen(arg);
	flag = (params->width > 0) ? params->width : params->mul;
	if (flag - len > 0)
	{
		i = 0;
		new = ft_strnew(flag);
		while (i < flag - len)
		{
			new[i] = ' ';
			i++;
		}
		ft_strcat(new, (const char *)arg);
		if (params->format == 'c' && arg[0] == '\0')
			new[i] = '\0';
		free(arg);
		if (params->format == 'c')
			params->length += flag - len;
		return (new);
	}
	return (arg);
}
