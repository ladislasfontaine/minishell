/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 16:58:27 by lafontai          #+#    #+#             */
/*   Updated: 2020/06/17 18:52:56 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// working great
// need to add ${key} to work

char	*get_var_value(t_minishell *data, char *key)
{
	t_list	*element;
	char	*key_elem;
	char	*value;

	value = NULL;
	element = data->env;
	while (element)
	{
		key_elem = ((t_var *)element->content)->key;
		if (ft_strequ(key_elem, key))
		{
			value = ft_strdup(((t_var *)element->content)->value);
			break ;
		}
		element = element->next;
	}
	if (!value)
		value = ft_strnew(0);
	return (value);
}

char	*get_var_key(char *str, int dollar)
{
	int		j;

	j = 0;
	while (str[dollar + 1 + j] && str[dollar + 1 + j] != ' ')
		j++;
	return (ft_substr(str, dollar + 1, j));
}

void	replace_key_by_value(t_minishell *data, t_command *cmd, t_var my_var, int dollar)
{
	char	*new_cmd;

	if (!(new_cmd = ft_strnew(ft_strlen(cmd->cmd) - ft_strlen(my_var.key) - 1 + ft_strlen(my_var.value))))
		exit_error(data);
	ft_strncat(new_cmd, cmd->cmd, dollar);
	ft_strcat(new_cmd, my_var.value);
	ft_strcat(new_cmd, cmd->cmd + dollar + 1 + ft_strlen(my_var.key));
	free(cmd->cmd);
	cmd->cmd = new_cmd;
}

void	replace_variables(t_minishell *data, t_command *cmd)
{
	int		i;
	t_var	my_var;

	i = 0;
	while (cmd->cmd[i])
	{
		// faire une fonction check_quotes
		if (cmd->cmd[i] == '\'' && cmd->s_quote == 0 && cmd->d_quote != 1)
			cmd->s_quote = 1;
		else if (cmd->cmd[i] == '\'' && cmd->s_quote == 1)
			cmd->s_quote = 0;
		else if (cmd->cmd[i] == '\"' && cmd->d_quote == 0  && cmd->s_quote != 1)
			cmd->d_quote = 1;
		else if (cmd->cmd[i] == '\"' && cmd->d_quote == 1)
			cmd->d_quote = 0;
		else if (cmd->cmd[i] == '$' && !cmd->s_quote)
		{
			my_var.key = NULL;
			my_var.value = NULL;
			if (!(my_var.key = get_var_key(cmd->cmd, i)))
				exit_error(data);
			if (!(my_var.value = get_var_value(data, my_var.key)))
			{
				free(my_var.key);
				exit_error(data);
			}
			replace_key_by_value(data, cmd, my_var, i);
			i += ft_strlen(my_var.value) - 1;
			free(my_var.key);
			free(my_var.value);
		}
		i++;
	}
	cmd->s_quote = 0;
	cmd->d_quote = 0;
}

