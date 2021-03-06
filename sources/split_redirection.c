/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 22:00:30 by lafontai          #+#    #+#             */
/*   Updated: 2020/08/04 17:44:12 by memartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	w_count(const char *s, char c)
{
	t_split	d;

	init_split(&d);
	if (s[0] != c)
		d.count++;
	while (s[d.i])
	{
		check_quotes(s[d.i], &d.s_quote, &d.d_quote);
		if (s[d.i] == '\\')
		{
			d.i = (s[d.i + 1]) ? d.i + 2 : d.i + 1;
			continue ;
		}
		if ((s[d.i] == '>' || s[d.i] == '<') && !d.s_quote && !d.d_quote)
		{
			d.count++;
			d.i += (s[d.i] == '>' && s[d.i + 1] && s[d.i + 1] == '>') ? 1 : 0;
		}
		if ((s[d.i] == c || s[d.i] == '>' || s[d.i] == '<')
			&& s[d.i + 1] && (s[d.i + 1] != c && s[d.i + 1] != '>'
			&& s[d.i + 1] != '<') && !d.s_quote && !d.d_quote)
			d.count++;
		d.i++;
	}
	return (d.count);
}

static int	w_len(const char *str, char c, int pos)
{
	t_split	d;
	int		esc;

	esc = 0;
	init_split(&d);
	if (str[pos] == '>' || str[pos] == '<')
	{
		if (str[pos] == '>' && str[pos + 1] && str[pos + 1] == '>')
			return (2);
		return (1);
	}
	while (str[pos + d.i] && ((str[pos + d.i] != '>' && str[pos + d.i] != c
			&& str[pos + d.i] != '<') || esc || d.s_quote || d.d_quote))
	{
		check_quotes(str[pos + d.i], &d.s_quote, &d.d_quote);
		check_escape(str, pos + d.i, &esc);
		d.count++;
		d.i++;
	}
	return (d.count + 1);
}

void		split_words(char const *s, t_split *d)
{
	d->tab[d->j] = ft_strnew(w_len(s, ' ', d->i));
	while (s[d->i] && ((s[d->i] != ' ' && s[d->i] != '>' && s[d->i] != '<')
			|| d->s_quote || d->d_quote || d->count))
	{
		check_quotes(s[d->i], &d->s_quote, &d->d_quote);
		if (!d->count && s[d->i] == '\\')
		{
			d->tab[d->j][d->k] = s[d->i];
			d->i++;
			d->k++;
			d->count = 1;
		}
		if (d->count
		|| (!d->s_quote && !d->d_quote && s[d->i] != '\'' && s[d->i] != '\"')
		|| (d->s_quote && s[d->i] != '\'') || (d->d_quote && s[d->i] != '\"'))
		{
			d->tab[d->j][d->k] = s[d->i];
			d->k++;
		}
		d->count = 0;
		d->i++;
	}
	d->tab[d->j][d->k] = '\0';
	d->j++;
}

void		split_chevrons(char const *s, t_split *d)
{
	d->tab[d->j] = ft_strnew(w_len(s, ' ', d->i));
	if (w_len(s, ' ', d->i) == 2)
	{
		d->tab[d->j][0] = '>';
		d->tab[d->j][1] = '>';
	}
	else
	{
		if (s[d->i] == '>')
			d->tab[d->j][0] = '>';
		else
			d->tab[d->j][0] = '<';
	}
	d->i += ft_strlen(d->tab[d->j]);
	d->j++;
}

char		**ft_split_special_redir(char const *s, char c)
{
	t_split	d;

	init_split(&d);
	if (!(d.tab = (char **)malloc(sizeof(char *) * (w_count(s, c) + 1))))
		return (NULL);
	if (s[0] && s[0] == '\\')
	{
		d.count = 1;
		d.i++;
	}
	while (s[d.i])
	{
		if ((d.count && s[d.i] != c)
		|| (s[d.i] && s[d.i] != c && s[d.i] != '>' && s[d.i] != '<'))
		{
			split_words(s, &d);
			d.k = 0;
		}
		else if (s[d.i] && !d.count && (s[d.i] == '>' || s[d.i] == '<'))
			split_chevrons(s, &d);
		else
			d.i++;
	}
	d.tab[d.j] = NULL;
	return (d.tab);
}
