/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 10:00:53 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/19 10:19:22 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include "libft.h"

typedef struct	s_arg
{
	int		flag_zero;
	int		flag_minus;
	int		mul;
	int		width;
	int		precision;
	int		dot;
	int		precision_mul;
	int		length;
	int		neg;
	char	format;
	t_list	**list;
}				t_arg;

int				ft_printf(const char *str, ...);
int				run_conversion(t_list **begin, char *format, va_list ap);
int				analyze_format(t_arg *params, char *format, va_list ap);

char			*isolate_format(const char *str, int i);
t_arg			*init_params(t_list **begin, char *format);
int				update_params(t_arg *params, char c, int num);
int				router(t_arg *params, va_list ap);
int				router_flags(t_arg *params, char **str);

char			*format_c(t_arg *params, va_list ap);
char			*format_s(va_list ap);
char			*format_d(t_arg *params, va_list ap);
char			*format_u(va_list ap);
char			*format_p(t_arg *params, va_list ap);
char			*format_x(va_list ap);
char			*format_x_maj(va_list ap);
char			*format_percent(void);

char			*flag_zero(t_arg *params, char *arg);
char			*flag_zero_neg(t_arg *params, char *arg);
char			*flag_zero_str(t_arg *params, char *arg);
char			*flag_zero_hex(t_arg *params, char *arg);
char			*flag_minus(t_arg *params, char *arg);
char			*flag_width(t_arg *params, char *arg);

int				utils_one(t_arg *params, char *format, int *i);
int				utils_two(t_arg *params, char *format, va_list ap, int *i);
int				utils_three(t_arg *params, char *format, int *i);
int				utils_four(t_arg *params, char *format, va_list ap, int *i);

int				add_element_in_list(t_list **begin, char *str, int n);
void			print_list(t_list *element, int *r);
int				read_string(t_list **begin, const char *str, int i);
void			clear_string(void *str);

#endif
