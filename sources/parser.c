/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 09:08:02 by lafontai          #+#    #+#             */
/*   Updated: 2020/06/19 11:05:59 by lafontai         ###   ########.fr       */
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
	else if (letter == '\"' && *d_quote == 0  && *s_quote != 1)
		*d_quote = 1;
	else if (letter == '\"' && *d_quote == 1)
		*d_quote = 0;
}
