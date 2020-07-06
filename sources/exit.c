/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 12:13:10 by lafontai          #+#    #+#             */
/*   Updated: 2020/07/06 15:20:47 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_command(void *element)
{
	t_command	*temp;

	temp = (t_command *)element;
	if (temp->args)
		free_tab(temp->args);
	if (temp->cmd)
		free(temp->cmd);
	if (temp)
		free(temp);
}

void	del_variable(void *element)
{
	t_var	*temp;

	temp = (t_var *)element;
	if (temp->key)
		free(temp->key);
	if (temp->value)
		free(temp->value);
	if (temp)
		free(temp);
}

void	clear_all(t_minishell *data)
{
	if (data)
	{
		if (data->line)
			free(data->line);
		data->line = NULL;
		ft_lstclear(&data->cmd, &del_command);
		ft_lstclear(&data->env, &del_variable);
		data->cmd = NULL;
		data->env = NULL;
	}
}

void	exit_error(t_minishell *data)
{
	clear_all(data);
	exit(1);
}

void	exit_normal(t_minishell *data)
{
	clear_all(data);
	ft_putstr_fd("exit\n", 2);
	exit(0);
}

void	command_exit(t_minishell *data, t_command *cmd)
{
	int	n;
	int	i;
	int	code;

	n = 0;
	while (cmd->args[n])
		n++;
	ft_putstr_fd("exit\n", 2);
	if (n == 1)
	{
		clear_all(data);
		exit(0);
	}
	else
	{
		i = 0;
		if (cmd->args[1][i] == '+' || cmd->args[1][i] == '-')
			i++;
		while (cmd->args[1][i] && ft_isdigit(cmd->args[1][i]))
			i++;
		if (cmd->args[1][i])
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(cmd->args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			clear_all(data);
			exit(255);
		}
		else if (cmd->args[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			clear_all(data);
			exit(1);
		}
		code = ft_atoi(cmd->args[1]);
		code = code % 256;
		clear_all(data);
		exit(code);
	}
}
