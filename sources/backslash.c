/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 11:11:46 by lafontai          #+#    #+#             */
/*   Updated: 2020/08/18 11:19:39 by lafontai         ###   ########.fr       */
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

void	remove_all_backslash(char **str, int *i, int *j)
{
	char	*tmp;

	while (str[*j][*i])
	{
		if (str[*j][*i] == '\\')
		{
			tmp = ft_strdup_except(str[*j], *i);
			ft_strdel(&str[*j]);
			str[*j] = tmp;
		}
		if (str[*j][*i])
			*i += 1;
	}
}

void	remove_specific_backslash(char **str, int *i, int *j)
{
	char	*tmp;

	while (str[*j][*i])
	{
		if (str[*j][*i] == '\\' && str[*j][*i + 1]
			&& (str[*j][*i + 1] == '$' || str[*j][*i + 1] == '\\'
			|| str[*j][*i + 1] == '\"' || str[*j][*i + 1] == '`'))
		{
			tmp = ft_strdup_except(str[*j], *i);
			ft_strdel(&str[*j]);
			str[*j] = tmp;
		}
		if (str[*j][*i])
			*i += 1;
	}
}

void	remove_backslash(char **str, t_command *cmd)
{
	int		i;
	int		j;

	j = 0;
	while (str[j])
	{
		i = 0;
		if (!cmd->was_in_quote[j])
			remove_all_backslash(str, &i, &j);
		else if (cmd->was_in_quote[j] == 2)
			remove_specific_backslash(str, &i, &j);
		j++;
	}
}
