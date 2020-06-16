/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 17:02:09 by lafontai          #+#    #+#             */
/*   Updated: 2020/06/16 10:54:15 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_len(long n)
{
	int	len;

	len = 1;
	if (n < 0)
	{
		len++;
		n = -n;
	}
	while (n > 9)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char		*ft_itoa(int n)
{
	char	*str;
	int		neg;
	int		len;
	long	num;

	num = n;
	len = num_len(num);
	str = ft_strnew(len);
	if (!str)
		return (NULL);
	neg = 0;
	if (num < 0)
	{
		neg = 1;
		num = -num;
		str[0] = '-';
	}
	while (len > 0)
	{
		if (!(len == 1 && neg))
			str[len - 1] = (num % 10) + 48;
		num = num / 10;
		len--;
	}
	return (str);
}
