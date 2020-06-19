/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_special.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 17:05:38 by lafontai          #+#    #+#             */
/*   Updated: 2020/06/19 10:38:14 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	check_quotes(char letter, int *s_quote, int *d_quote)
{
	if (letter == '\'' && *s_quote == 0 && *d_quote != 1)
		*s_quote = 1;
	else if (letter == '\'' && *s_quote == 1)
		*s_quote = 0;
	else if (letter == '\"' && *d_quote == 0  && *s_quote != 1)
		*d_quote = 1;
	else if (letter == '\"' && *d_quote == 1)
		*d_quote = 0;
}

static int	w_count(const char *str, char c)
{
	int	count;
	int	i;
	int	s_quote;
	int	d_quote;

	s_quote = 0;
	d_quote = 0;
	count = 0;
	i = 0;
	if (str[0] != c)
		count++;
	while (str[i] && str[i + 1])
	{
		check_quotes(str[i], &s_quote, &d_quote);
		if (str[i] == c && str[i + 1] != c && !s_quote && !d_quote)
			count++;
		i++;
	}
	return (count);
}

static int	w_len(const char *str, char c, int pos)
{
	int	i;
	int	count;
	int	s_quote;
	int	d_quote;

	s_quote = 0;
	d_quote = 0;
	count = 0;
	i = 0;
	while (str[pos + i] && (str[pos + i] != c || s_quote || d_quote))
	{
		check_quotes(str[pos + i], &s_quote, &d_quote);
		if (!s_quote && !d_quote && str[pos + i] != '\'' && str[pos + i] != '\"')
			count++;
		else if ((s_quote && str[pos + i] != '\'') || (d_quote && str[pos + i] != '\"'))
			count++;
		i++;
	}
	return (count);
}

char		**ft_split_special(char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;
	int		k;
	int	s_quote;
	int	d_quote;

	if (!(tab = (char **)malloc(sizeof(char *) * (w_count(s, c) + 1))))
		return (NULL);
	s_quote = 0;
	d_quote = 0;
	i = 0;
	j = 0;
	k = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			tab[j] = ft_strnew(w_len(s, c, i));
			while (s[i] && (s[i] != c || s_quote || d_quote))
			{
				check_quotes(s[i], &s_quote, &d_quote);
				if ((!s_quote && !d_quote && s[i] != '\'' && s[i] != '\"')
					|| (s_quote && s[i] != '\'') || (d_quote && s[i] != '\"'))
				{
					tab[j][k] = s[i];
					k++;
				}
				i++;
			}
			tab[j][k] = '\0';
			k = 0;
			j++;
		}
		else
			i++;
	}
	tab[j] = NULL;
	return (tab);
}
