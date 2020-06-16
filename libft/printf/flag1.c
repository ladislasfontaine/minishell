/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 16:52:16 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/06 08:01:58 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

char	*flag_zero(t_arg *params, char *arg)
{
	int		i;
	int		diff;
	int		flag;
	char	*new;

	flag = (params->flag_zero > params->precision) ?
		params->flag_zero : params->precision;
	diff = flag - ft_strlen(arg);
	if (diff > 0)
	{
		new = ft_strnew(flag);
		i = 0;
		while (i < diff + params->neg)
		{
			new[i] = '0';
			i++;
		}
		ft_strcat(new, (const char *)arg);
		free(arg);
		return (new);
	}
	else
		return (arg);
}

char	*flag_zero_neg(t_arg *params, char *arg)
{
	int		i;
	int		diff;
	int		flag;
	char	*new;

	flag = (params->flag_zero > params->precision) ?
		params->flag_zero : params->precision + 1;
	diff = flag - ft_strlen(arg);
	if (diff > 0)
	{
		new = ft_strnew(flag);
		new[0] = '-';
		i = 1;
		while (i < (diff + params->neg))
		{
			new[i] = '0';
			i++;
		}
		ft_strcat(new, (const char *)(arg + 1));
		free(arg);
		return (new);
	}
	else
		return (arg);
}

char	*flag_zero_str(t_arg *params, char *arg)
{
	int		diff;
	size_t	max_len;
	char	*new;

	max_len = params->precision;
	diff = max_len - ft_strlen(arg);
	if (diff < 0)
	{
		new = ft_strnew(max_len);
		ft_strncpy(new, (const char *)arg, max_len);
		free(arg);
		return (new);
	}
	else
		return (arg);
}

char	*flag_zero_hex(t_arg *params, char *arg)
{
	int		diff;
	int		i;
	size_t	min_len;
	char	*new;

	min_len = params->precision + 2;
	diff = min_len - ft_strlen(arg);
	if (diff > 0)
	{
		new = ft_strnew(min_len);
		new[0] = '0';
		new[1] = 'x';
		i = 2;
		while (i < diff + 2)
		{
			new[i] = '0';
			i++;
		}
		ft_strcat(new, (const char *)(arg + 2));
		free(arg);
		return (new);
	}
	else
		return (arg);
}
