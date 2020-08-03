/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 22:00:30 by lafontai          #+#    #+#             */
/*   Updated: 2020/08/03 13:32:04 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	w_count(const char *str, char c)
{
	t_split	d;

	init_split(&d);
	if (str[0] != c)
		d.count++;
	while (str[d.i] && str[d.i + 1])
	{
		check_quotes(str[d.i], &d.s_quote, &d.d_quote);
		if (str[d.i] == '\\')
		{
			d.i += 2;
			continue ;
		}
		if ((str[d.i] == '>' || str[d.i] == '<') && !d.s_quote && !d.d_quote)
		{
			d.count++;
			d.i = (str[d.i] == '>' && str[d.i + 1] == '>') ? d.i + 1 : d.i;
		}
		if ((str[d.i] == c || str[d.i] == '>' || str[d.i] == '<')
			&& str[d.i + 1] && (str[d.i + 1] != c && str[d.i + 1] != '>'
			&& str[d.i + 1] != '<') && !d.s_quote && !d.d_quote)
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
		if (!d.s_quote && !d.d_quote && str[pos + d.i] != '\''
			&& str[pos + d.i] != '\"')
			d.count++;
		else if ((d.s_quote && str[pos + d.i] != '\'')
				|| (d.d_quote && str[pos + d.i] != '\"'))
			d.count++;
		check_escape(str, pos + d.i, &esc);
		d.i++;
	}
	return (d.count);
}

void		split_words(char const *s, t_split *d)
{
	d->tab[d->j] = ft_strnew(w_len(s, ' ', d->i));
	while (s[d->i] && ((s[d->i] != ' ' && s[d->i] != '>' && s[d->i] != '<')
			|| d->s_quote || d->d_quote || d->count))
	{
		check_quotes(s[d->i], &d->s_quote, &d->d_quote);
		if ((!d->count && s[d->i] == '\\' && !d->s_quote && !d->d_quote)
		|| (!d->count && s[d->i] == '\\' && s[d->i + 1] && (s[d->i + 1] == '$'
		|| s[d->i + 1] == '\"' || s[d->i + 1] == '\'' || s[d->i + 1] == '>'
		|| s[d->i + 1] == '<')))
		{
			write_backslash(s, d);
			continue ;
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
		|| (s[d.i] != c && s[d.i] != '>' && s[d.i] != '<'))
		{
			split_words(s, &d);
			d.k = 0;
		}
		else if (!d.count && (s[d.i] == '>' || s[d.i] == '<'))
			split_chevrons(s, &d);
		else
			d.i++;
	}
	d.tab[d.j] = NULL;
	return (d.tab);
}
