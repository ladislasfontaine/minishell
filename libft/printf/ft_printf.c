/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 16:52:57 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/08 16:12:48 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		analyze_format(t_arg *params, char *format, va_list ap)
{
	int	i;

	i = 1;
	while (format[i] && format[i] != params->format)
		if (format[i] == '0' || format[i] == '-' || format[i] == '.')
			if (format[i + 1] == '*' && utils_two(params, format, ap, &i))
				continue ;
			else if ((ft_isdigit(format[i + 1]) || format[i] == '.') &&
					utils_one(params, format, &i))
				continue ;
			else
				i++;
		else if (ft_isdigit(format[i]))
		{
			if (!utils_three(params, format, &i))
				return (0);
		}
		else if (format[i] == '*')
		{
			if (!utils_four(params, format, ap, &i))
				return (0);
		}
		else
			return (0);
	return (1);
}

int		run_conversion(t_list **begin, char *format, va_list ap)
{
	t_arg	*params;

	params = init_params(begin, format);
	if (ft_strlen(format) < 2 ||
		(ft_strlen(format) > 2 && !analyze_format(params, format, ap)))
	{
		free(params);
		return (0);
	}
	if (!router(params, ap))
	{
		free(params);
		return (0);
	}
	free(params);
	return (1);
}

int		ft_printf(const char *str, ...)
{
	t_list	*begin;
	va_list	args;
	char	*format;
	int		i;
	int		result;

	begin = NULL;
	i = 0;
	va_start(args, str);
	while (str[i])
	{
		i = read_string(&begin, str, i);
		if (str[i] == '%')
		{
			format = isolate_format(str, i);
			run_conversion(&begin, format, args);
			i += ft_strlen(format);
			free(format);
		}
	}
	va_end(args);
	result = 0;
	print_list(begin, &result);
	ft_lstclear(&begin, &clear_string);
	return (result);
}
