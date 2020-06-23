/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_special_redir.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 17:05:38 by lafontai          #+#    #+#             */
/*   Updated: 2020/06/23 14:23:26 by lafontai         ###   ########.fr       */
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
		if ((str[i] == '>' || str[i] == '<') && !s_quote && !d_quote)
		{
			count++;
			if (str[i] == '>' && str[i + 1] == '>')
				i++;
		}
		if ((str[i] == c || str[i] == '>' || str[i] == '<') && str[i + 1]
			&& (str[i + 1] != c && str[i + 1] != '>' && str[i + 1] != '<')
			&& !s_quote && !d_quote)
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
	if (str[pos] == '>' || str[pos] == '<')
	{
		if (str[pos] == '>' && str[pos + 1] && str[pos + 1] == '>')
			return (2);
		return (1);
	}
	while (str[pos + i] && ((str[pos + i] != c && str[pos + i] != '>' && str[pos + i] != '<') || s_quote || d_quote))
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

char		**ft_split_special_redir(char const *s, char c)
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
		if (s[i] != c && s[i] != '>' && s[i] != '<')
		{
			tab[j] = ft_strnew(w_len(s, c, i));
			while (s[i] && ((s[i] != c && s[i] != '>' && s[i] != '<') || s_quote || d_quote))
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
		else if (s[i] == '>' || s[i] == '<')
		{
			tab[j] = ft_strnew(w_len(s, c, i));
			if (w_len(s, c, i) == 2)
			{
				tab[j][0] = '>';
				tab[j][1] = '>';
			}
			else
				if (s[i] == '>')
					tab[j][0] = '>';
				else
					tab[j][0] = '<';
			i += ft_strlen(tab[j]);
			j++;
		}
		else
			i++;
	}
	tab[j] = NULL;
	return (tab);
}