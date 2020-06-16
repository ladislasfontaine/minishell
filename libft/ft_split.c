/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 17:05:38 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/04 16:32:18 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	w_count(const char *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (str[0] != c)
		count++;
	while (str[i] && str[i + 1])
	{
		if (str[i] == c && str[i + 1] != c)
			count++;
		i++;
	}
	return (count);
}

static int	w_len(const char *str, char c, int pos)
{
	int	count;

	count = 0;
	while (str[pos + count] != c && str[pos + count])
		count++;
	return (count);
}

char		**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;

	if (!(tab = (char **)malloc(sizeof(char *) * (w_count(s, c) + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			tab[j] = ft_substr(s, i, w_len(s, c, i));
			i += w_len(s, c, i);
			j++;
		}
		else
			i++;
	}
	tab[j] = NULL;
	return (tab);
}
