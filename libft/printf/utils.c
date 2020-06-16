/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 09:43:07 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/06 09:43:30 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		utils_one(t_arg *params, char *format, int *i)
{
	int		num;
	int		zeroes;

	zeroes = 0;
	num = ft_atoi((const char *)&format[*i + 1]);
	while (num != 0 && format[*i + 1 + zeroes] &&
			format[*i + 1 + zeroes] == '0')
		zeroes++;
	if (!update_params(params, format[*i], num))
		return (0);
	if (format[*i] == '.' && !ft_isdigit(format[*i + 1]))
		*i += 1 + zeroes;
	else
		*i += ft_numlen(num) + 1 + zeroes;
	return (1);
}

int		utils_two(t_arg *params, char *format, va_list ap, int *i)
{
	int		num;

	num = (int)va_arg(ap, int);
	if (!update_params(params, format[*i], num))
		return (0);
	*i += 2;
	return (1);
}

int		utils_three(t_arg *params, char *format, int *i)
{
	int		num;

	num = ft_atoi((const char *)&format[*i]);
	if (!update_params(params, format[*i], num))
		return (0);
	*i += ft_numlen(num);
	return (1);
}

int		utils_four(t_arg *params, char *format, va_list ap, int *i)
{
	int		num;

	num = (int)va_arg(ap, int);
	if (!update_params(params, format[*i], num))
		return (0);
	*i += 1;
	return (1);
}
