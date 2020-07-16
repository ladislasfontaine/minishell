/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 09:08:02 by lafontai          #+#    #+#             */
/*   Updated: 2020/07/16 15:53:26 by memartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_spaces(char *str)
{
	while (*str && *str == ' ')
		str++;
	return (str);
}

char	*dup_first_word(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	return (ft_substr(str, 0, i));
}

void	check_quotes(char letter, int *s_quote, int *d_quote)
{
	if (letter == '\'' && *s_quote == 0 && *d_quote != 1)
		*s_quote = 1;
	else if (letter == '\'' && *s_quote == 1)
		*s_quote = 0;
	else if (letter == '\"' && *d_quote == 0 && *s_quote != 1)
		*d_quote = 1;
	else if (letter == '\"' && *d_quote == 1)
		*d_quote = 0;
}

int		split_line(t_minishell *data)
{
	int			old_i;
	int			i;

	i = 0;
	old_i = 0;
	while (data->line[i])
	{
		check_quotes(data->line[i], &data->s_quote, &data->d_quote);
		if ((data->line[i] == '|' || data->line[i] == ';')
			&& !data->s_quote && !data->d_quote)
		{
			if (data->line[i] == '|')
				data->separator = PIPE;
			if (data->line[i] == ';')
				data->separator = SEMI_COLON;
			create_command(data, old_i, i);
			old_i = i + 1;
		}
		i++;
	}
	create_command(data, old_i, i - 1);
	return (0);
}
