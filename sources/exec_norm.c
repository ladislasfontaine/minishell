/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_norm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 14:38:46 by memartin          #+#    #+#             */
/*   Updated: 2020/07/16 14:43:52 by memartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **tab)
{
	int	i;

	if (tab)
	{
		i = 0;
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}

char	**create_env_tab(t_minishell *data)
{
	t_list	*element;
	t_var	*var;
	char	**tab;
	int		size;
	int		i;

	size = ft_lstsize(data->env);
	tab = (char **)malloc(sizeof(char *) * (size + 1));
	element = data->env;
	i = 0;
	while (i < size)
	{
		var = (t_var *)element->content;
		tab[i] = ft_strjoin_with(var->key, var->value, '=');
		i++;
		element = element->next;
	}
	tab[i] = 0;
	return (tab);
}
