/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_special.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 21:56:38 by lafontai          #+#    #+#             */
/*   Updated: 2020/07/16 22:02:35 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	w_len(const char *str, char c, int k)
{
	int	i;
	int	count;
	int	s_quote;
	int	d_quote;

	s_quote = 0;
	d_quote = 0;
	count = 0;
	i = 0;
	while (str[k + i] && (str[k + i] != c || s_quote || d_quote))
	{
		check_quotes(str[k + i], &s_quote, &d_quote);
		if (!s_quote && !d_quote && str[k + i] != '\'' && str[k + i] != '\"')
			count++;
		else if ((s_quote && str[k + i] != '\'')
				|| (d_quote && str[k + i] != '\"'))
			count++;
		i++;
	}
	return (count);
}

void		split_word(char const *s, t_split *d)
{
	while (s[d->i] && (s[d->i] != ' ' || d->s_quote || d->d_quote))
	{
		check_quotes(s[d->i], &d->s_quote, &d->d_quote);
		if ((!d->s_quote && !d->d_quote && s[d->i] != '\'' && s[d->i] != '\"')
		|| (d->s_quote && s[d->i] != '\'') || (d->d_quote && s[d->i] != '\"'))
		{
			d->tab[d->j][d->k] = s[d->i];
			d->k++;
		}
		d->i++;
	}
}

char		**ft_split_special(char const *s, char c)
{
	t_split	d;

	init_split(&d);
	if (!(d.tab = (char **)malloc(sizeof(char *) * (w_count(s, c) + 1))))
		return (NULL);
	while (s[d.i])
	{
		if (s[d.i] != c)
		{
			d.tab[d.j] = ft_strnew(w_len(s, c, d.i));
			split_word(s, &d);
			d.tab[d.j][d.k] = '\0';
			d.k = 0;
			d.j++;
		}
		else
			d.i++;
	}
	d.tab[d.j] = NULL;
	return (d.tab);
}
