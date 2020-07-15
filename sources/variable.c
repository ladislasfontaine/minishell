/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 16:58:27 by lafontai          #+#    #+#             */
/*   Updated: 2020/07/15 19:02:37 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*get_var_key(char *str, int dollar, int *bracket, int d_quote)
{
	int		j;

	j = 0;
	if (str[dollar + 1] == '{')
	{
		while (str[dollar + 2 + j] && str[dollar + 2 + j] != '}')
			j++;
		*bracket = 1;
	}
	else if (d_quote)
		while (str[dollar + 1 + j] && str[dollar + 1 + j] != ' ' && str[dollar + 1 + j] != '$' && str[dollar + 1 + j] != '=' && str[dollar + 1 + j] != '\\' && str[dollar + 1 + j] != '\'' && str[dollar + 1 + j] != '\"' && str[dollar + 1 + j] != '\"')
			j++;
	else
		while (str[dollar + 1 + j] && str[dollar + 1 + j] != ' ' && str[dollar + 1 + j] != '$' && str[dollar + 1 + j] != '=' && str[dollar + 1 + j] != '\\' && str[dollar + 1 + j] != '\'' && str[dollar + 1 + j] != '\"')
			j++;
	return (ft_substr(str, dollar + *bracket + 1, j));
}

void	replace_key_by_value(t_minishell *data, t_command *cmd, t_var my_var, int dollar)
{
	char	*new_cmd;

	if (!(new_cmd = ft_strnew(ft_strlen(cmd->cmd) - ft_strlen(my_var.key) - 1 - (2 * my_var.local) + ft_strlen(my_var.value))))
		exit_error(data);
	ft_strncat(new_cmd, cmd->cmd, dollar);
	ft_strcat(new_cmd, my_var.value);
	ft_strcat(new_cmd, cmd->cmd + dollar + 1 + ft_strlen(my_var.key) + (2 * my_var.local));
	free(cmd->cmd);
	cmd->cmd = new_cmd;
}

void	replace_variables(t_minishell *data, t_command *cmd)
{
	int		i;
	int		esc;
	t_var	my_var;

	i = 0;
	esc = 0;
	while (cmd->cmd[i])
	{
		check_quotes(cmd->cmd[i], &cmd->s_quote, &cmd->d_quote);
		if (!esc && cmd->cmd[i] == '\\' && !cmd->s_quote)
		{
			esc = 1;
			i++;
			continue ;
		}
		if (!esc && cmd->cmd[i] == '$' && !cmd->s_quote)
		{
			my_var.key = NULL;
			my_var.value = NULL;
			my_var.local = 0;
			if (cmd->cmd[i + 1] && cmd->cmd[i + 1] == '?')
				my_var.key = ft_strdup("?");
			else if (!(my_var.key = get_var_key(cmd->cmd, i, &my_var.local, cmd->d_quote)))
				exit_error(data);
			if (ft_strlen(my_var.key) == 0)
			{
				i++;
				continue ;
			}
			else if (ft_strequ(my_var.key, "?"))
			{
				if (!(my_var.value = ft_itoa(data->exit)))
				{
					free(my_var.key);
					exit_error(data);
				}
			}
			else if (!(my_var.value = get_var_value(data, my_var.key)))
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
		esc = 0;
	}
	cmd->s_quote = 0;
	cmd->d_quote = 0;
}
