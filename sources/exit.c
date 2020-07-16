/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 12:13:10 by lafontai          #+#    #+#             */
/*   Updated: 2020/07/16 15:28:07 by memartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			exit_error(t_minishell *data)
{
	clear_all(data);
	exit(data->exit);
}

void			exit_normal(t_minishell *data)
{
	clear_all(data);
	ft_putstr_fd("exit\n", 2);
	exit(0);
}

static void		command_exit_norm(t_minishell *data, t_command *cmd)
{
	int		i;

	i = 0;
	if (cmd->args[1][i] == '+' || cmd->args[1][i] == '-')
		i++;
	while (cmd->args[1][i] && ft_isdigit(cmd->args[1][i]))
		i++;
	if (cmd->args[1][i])
	{
		print_error_exit(cmd->args[1]);
		clear_all(data);
		exit(2);
	}
	else if (cmd->args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		clear_all(data);
		exit(1);
	}
}

void			command_exit(t_minishell *data, t_command *cmd)
{
	int		n;
	int		code;

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
		command_exit_norm(data, cmd);
		code = ft_atoi(cmd->args[1]);
		code = code % 256;
		clear_all(data);
		exit(code);
	}
}
