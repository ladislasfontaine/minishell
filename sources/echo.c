/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 14:09:09 by lafontai          #+#    #+#             */
/*   Updated: 2020/06/23 16:48:25 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_echo(t_minishell *data, t_command *cmd, char *str)
{
	int		option;
	int		i;

	(void)data;
	(void)str;
	option = (cmd->args[1] && ft_strequ(cmd->args[1], "-n")) ? 1 : 0;
	i = option ? 2 : 1;
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
