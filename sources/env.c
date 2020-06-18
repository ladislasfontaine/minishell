/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 10:47:40 by lafontai          #+#    #+#             */
/*   Updated: 2020/06/17 15:39:24 by memartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	*create_var(char *str)
{
	int		equal;
	t_var	*var;

	equal = 0;
	while (str[equal] && str[equal] != '=')
		equal++;
	if ((size_t)equal == ft_strlen(str))
		return (NULL);
	if (!(var = (t_var *)malloc(sizeof(t_var))))
		return (NULL);
	var->key = ft_substr(str, 0, equal);
	var->value = ft_substr(str, equal + 1, ft_strlen(str) - equal - 1);
	var->local = 0;
	return (var);
}

void	init_env(t_minishell *data, char **env)
{
	int		i;
	t_var	*tmp;
	t_list	*new;

	(void)data;
	i = 0;
	while (env[i])
	{
		if (!(tmp = create_var(env[i])))
			exit_error(data);
		if (!(new = ft_lstnew((void *)tmp)))
		{
			free(tmp);
			exit_error(data);
		}
		ft_lstadd_back(&data->env, new);
		i++;
	}
}

static void		print_env(void *element)
{
	t_var		*var;

	var = (t_var*)element;
	if (!var->local)
		ft_printf("%s=%s\n", var->key, var->value);
}

void			env(t_minishell *data)
{
	ft_lstiter(data->env, &print_env);
}
