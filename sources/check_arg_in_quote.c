/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg_in_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 15:35:14 by memartin          #+#    #+#             */
/*   Updated: 2020/08/03 15:19:55 by lafontai         ###   ########.fr       */
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

static int	*create_tab(t_command *cmd)
{
	int		*tab;
	int		i;

	i = 0;
	cmd->nb_arg = w_count(cmd->cmd, ' ');
	if (!(tab = (int*)malloc(sizeof(int) * cmd->nb_arg + 1)))
		return (NULL);
	while (i < cmd->nb_arg)
		tab[i++] = 0;
	return (tab);
}

static int	*fill_tab(t_command *cmd, int *tab)
{
	t_split		d;
	int			i;
	int			j;

	init_split(&d);
	i = 0;
	j = 0;
	while (cmd->cmd[i])
	{
		while (cmd->cmd[i] && is_whitespace(cmd->cmd[i]))
			i++;
		if (cmd->cmd[i] == '\'' || cmd->cmd[i] == '\"')
		{
			tab[j] = 1;
			check_quotes(cmd->cmd[i++], &d.s_quote, &d.d_quote);
			while (cmd->cmd[i] && (d.s_quote || d.d_quote))
				check_quotes(cmd->cmd[i++], &d.s_quote, &d.d_quote);
		}
		j++;
		while (cmd->cmd[i] && !is_whitespace(cmd->cmd[i]))
			i++;
	}
	return (tab);
}

int			*check_arg_in_quote(t_command *cmd)
{
	int		*tab;

	tab = create_tab(cmd);
	if (tab == NULL)
		return (tab);
	tab = fill_tab(cmd, tab);
	return (tab);
}
