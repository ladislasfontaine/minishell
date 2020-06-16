/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 08:07:41 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/07 14:32:07 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

char	*isolate_format(const char *str, int i)
{
	int		count;
	char	c;

	count = 1;
	c = str[i + count];
	while (c && !(c == 'c' || c == 's' || c == 'p' || c == 'd'
	|| c == 'i' || c == 'u' || c == 'x' || c == 'X' || c == '%'))
	{
		count++;
		c = str[i + count];
	}
	return (ft_substr(str, i, count + 1));
}

t_arg	*init_params(t_list **begin, char *format)
{
	t_arg	*new;

	new = (t_arg *)malloc(sizeof(t_arg));
	if (!new)
		return (NULL);
	new->flag_zero = 0;
	new->flag_minus = 0;
	new->mul = 0;
	new->width = 0;
	new->precision = 0;
	new->dot = 0;
	new->precision_mul = 0;
	new->length = 0;
	new->neg = 0;
	new->format = format[ft_strlen(format) - 1];
	new->list = begin;
	return (new);
}

int		update_params(t_arg *params, char c, int num)
{
	if (num < 0 && (c == '*' || c == '0' || c == '-'))
		params->flag_minus = -num;
	else if (num < 0)
		return (1);
	else if (c == '0')
		params->flag_zero = num;
	else if (ft_isdigit(c))
		params->width = num;
	else if (c == '-')
		params->flag_minus = num;
	else if (c == '.' && (params->dot = 1))
		params->precision = num;
	else if (c == '*')
		params->mul = num;
	else
		return (0);
	if (params->dot && params->flag_zero > params->precision &&
		params->format != '%')
	{
		params->width = params->flag_zero;
		params->flag_zero = 0;
	}
	if (params->format == '%' && params->flag_zero > 0 && !(params->dot = 0))
		params->precision = 0;
	return (1);
}

int		router_flags(t_arg *params, char **str)
{
	if (params->dot && params->precision == 0 &&
		*str[0] == '0' && ft_strlen(*str) == 1)
		ft_strclr(*str);
	if (params->precision > 0 && params->format == 'p')
		*str = flag_zero_hex(params, *str);
	else if (params->precision > 0 && !(params->format == 'c' ||
		params->format == 's' || params->format == '%') && params->neg)
		*str = flag_zero_neg(params, *str);
	else if (params->precision > 0 && !(params->format == 'c' ||
		params->format == 's' || params->format == '%'))
		*str = flag_zero(params, *str);
	if (params->dot && params->format == 's')
		*str = flag_zero_str(params, *str);
	if (params->width > 0 || params->mul > 0)
		*str = flag_width(params, *str);
	else if (params->flag_zero > 0 && params->neg)
		*str = flag_zero_neg(params, *str);
	else if (params->flag_zero > 0)
		*str = flag_zero(params, *str);
	else if (params->flag_minus > 0)
		*str = flag_minus(params, *str);
	return (1);
}

int		router(t_arg *params, va_list ap)
{
	char	*str;

	if (params->format == 's')
		str = format_s(ap);
	else if (params->format == 'd' || params->format == 'i')
		str = format_d(params, ap);
	else if (params->format == 'c')
		str = format_c(params, ap);
	else if (params->format == '%')
		str = format_percent();
	else if (params->format == 'u')
		str = format_u(ap);
	else if (params->format == 'x')
		str = format_x(ap);
	else if (params->format == 'X')
		str = format_x_maj(ap);
	else if (params->format == 'p')
		str = format_p(params, ap);
	else
		return (0);
	router_flags(params, &str);
	if (add_element_in_list(params->list, str, params->length))
		return (1);
	return (0);
}
