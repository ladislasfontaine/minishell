/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 18:31:26 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/11 11:46:41 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_count_nbr(int nbr, char *base, int *count)
{
	int		base_len;

	if (nbr < 0)
	{
		*count += 1;
		nbr = -nbr;
	}
	base_len = ft_strlen(base);
	if (nbr > base_len - 1)
		ft_count_nbr(nbr / base_len, base, count);
	*count += 1;
}

static int	ft_convert_base_from(char *str, char *base, int i, int neg)
{
	int	nb;
	int	char_in_base;
	int	j;

	nb = 0;
	while (str[i])
	{
		j = -1;
		char_in_base = -1;
		while (base[++j])
		{
			if (base[j] == str[i])
				char_in_base = j;
		}
		if (char_in_base != -1)
			nb = nb * ft_strlen(base) + char_in_base;
		if (char_in_base == -1 || (size_t)i == ft_strlen(str) - 1)
		{
			if (neg % 2 != 0)
				nb = -nb;
			return (nb);
		}
		i++;
	}
	return (0);
}

static int	ft_atoi_base(char *str, char *base)
{
	int	i;
	int	neg;

	i = 0;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n' ||
			str[i] == '\r' || str[i] == '\t' || str[i] == '\v')
		i++;
	neg = 0;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg++;
		i++;
	}
	return (ft_convert_base_from(str, base, i, neg));
}

char		*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	int		result_int;
	int		count;
	int		*count_ptr;
	char	*result_str;

	if (ft_no_error(base_from) && ft_no_error(base_to))
	{
		result_int = ft_atoi_base(nbr, base_from);
		count = 1;
		count_ptr = &count;
		ft_count_nbr(result_int, base_to, count_ptr);
		result_str = (char*)malloc(sizeof(char) * count);
		if (result_str == NULL)
			return (NULL);
		result_str[0] = '\0';
		ft_putnbr_base(result_int, base_to, result_str);
		return (result_str);
	}
	return (NULL);
}
