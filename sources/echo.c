/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 14:09:09 by lafontai          #+#    #+#             */
/*   Updated: 2020/06/25 15:52:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_echo(t_command *cmd)
{
	int		option;
	int		i;

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
