/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itohex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 08:40:35 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/05 08:41:39 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	hex_len(unsigned int n)
{
	int	len;

	len = 1;
	while (n > 15)
	{
		n = n / 16;
		len++;
	}
	return (len);
}

char		*ft_itohex(unsigned int n, char *base)
{
	char			*str;
	int				len;

	len = hex_len(n);
	str = ft_strnew(len);
	if (!str)
		return (NULL);
	while (len > 0)
	{
		str[len - 1] = base[n % 16];
		n = n / 16;
		len--;
	}
	return (str);
}
