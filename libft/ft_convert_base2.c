/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 19:01:38 by lafontai          #+#    #+#             */
/*   Updated: 2020/02/12 17:14:05 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_no_error(char *base)
{
	int	i;
	int	j;

	if ((int)ft_strlen(base) == 0 || (int)ft_strlen(base) == 1)
		return (0);
	i = 0;
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-'
			|| base[i] == ' ' || base[i] == '\f' || base[i] == '\n'
			|| base[i] == '\r' || base[i] == '\t' || base[i] == '\v')
			return (0);
		j = i;
		while (base[j])
		{
			if (j != i && base[j] == base[i])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	ft_strcat_char(char *dest, char c)
{
	int	dest_len;

	dest_len = 0;
	while (dest[dest_len])
		dest_len++;
	dest[dest_len] = c;
	dest_len++;
	dest[dest_len] = '\0';
}

void	ft_putnbr_base(int nbr, char *base, char *result)
{
	int		base_len;
	int		index;

	if (nbr < 0)
	{
		ft_strcat_char(result, '-');
		nbr = -nbr;
	}
	base_len = ft_strlen(base);
	if (nbr > base_len - 1)
	{
		ft_putnbr_base(nbr / base_len, base, result);
	}
	index = nbr % base_len;
	ft_strcat_char(result, base[index]);
}
