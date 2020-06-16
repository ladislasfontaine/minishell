/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 08:40:56 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/05 12:12:54 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	numlen(long n)
{
	int	count;

	count = 1;
	if (n < 0)
	{
		count++;
		n = -n;
	}
	while (n > 9)
	{
		count++;
		n = n / 10;
	}
	return (count);
}

char		*ft_itoa_u(unsigned int n)
{
	char			*str;
	int				len;
	unsigned int	num;

	num = n;
	len = numlen(num);
	if (!(str = ft_strnew(len)))
		return (NULL);
	while (len > 0)
	{
		str[len - 1] = (num % 10) + 48;
		num = num / 10;
		len--;
	}
	return (str);
}
