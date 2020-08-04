/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 14:09:09 by lafontai          #+#    #+#             */
/*   Updated: 2020/08/04 17:20:20 by memartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup_except(const char *s1, int i)
{
	char	*s2;
	int		j;
	int		k;

	s2 = (char *)malloc(ft_strlen((char *)s1));
	if (!s2)
		return (NULL);
	j = 0;
	k = 0;
	while (s1[j])
	{
		if (j != i)
		{
			s2[k] = s1[j];
			k++;
		}
		j++;
	}
	s2[k] = '\0';
	return (s2);
}

void	remove_backslash(char **str, t_command *cmd)
{
	int		i;
	int		j;
	int		s_quote;
	int		d_quote;
	char	*tmp;

	j = 0;
	while (str[j])
	{
		i = 0;
		s_quote = 0;
		d_quote = 0;
		if (!cmd->was_in_quote[j])
		{
			while (str[j][i])
			{
				check_quotes(str[j][i], &s_quote, &d_quote);
				if (str[j][i] == '\\' && !s_quote && !d_quote)
				{
					tmp = ft_strdup_except(str[j], i);
					ft_strdel(&str[j]);
					str[j] = tmp;
				}
				if (str[j][i])
					i++;
			}
		}
		j++;
	}
}

void	command_echo(t_minishell *data, t_command *cmd)
{
	int		option;
	int		i;

	data->exit = 0;
	option = (cmd->args[1] && ft_strequ(cmd->args[1], "-n")) ? 1 : 0;
	i = option ? 2 : 1;
	while (option && cmd->args[i] && ft_strequ(cmd->args[i], "-n"))
		i++;
	while (cmd->args[i])
	{
		ft_printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			ft_printf(" ");
		i++;
	}
	if (!option)
		ft_printf("\n");
}
