/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg_in_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 15:35:14 by memartin          #+#    #+#             */
/*   Updated: 2020/07/30 16:15:50 by memartin         ###   ########.fr       */
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

int			*check_arg_in_quote(t_command *cmd)
{
	int		*tab;
	int		i;
	int		j;

	i = 0;
	j = 0;
	cmd->nb_arg = w_count(cmd->cmd, ' ');
	if (!(tab = (int*)malloc(sizeof(int) * cmd->nb_arg + 1)))
		return (NULL);
	while (cmd->cmd[i])
	{
		while (cmd->cmd[i] && is_whitespace(cmd->cmd[i]))
			i++;
		if (cmd->cmd[i] != '\'' && cmd->cmd[i] != '\"')
			tab[j] = 0;
		else
			tab[j] = 1;
		j++;
		while (cmd->cmd[i] && !is_whitespace(cmd->cmd[i]))
			i++;
	}
	tab[j] = 0;
	return (tab);
}
