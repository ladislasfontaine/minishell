/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg_in_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 15:35:14 by memartin          #+#    #+#             */
/*   Updated: 2020/08/03 14:18:58 by memartin         ###   ########.fr       */
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
		if ((str[d.i] == '>' || str[d.i] == '<') && !d.s_quote && !d.d_quote)
		{
			d.count++;
			if (str[d.i] == '>' && str[d.i + 1] == '>')
				d.i++;
		}
		if ((str[d.i] == c || str[d.i] == '>' || str[d.i] == '<')
			&& str[d.i + 1] && (str[d.i + 1] != c && str[d.i + 1] != '>'
			&& str[d.i + 1] != '<') && !d.s_quote && !d.d_quote)
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
