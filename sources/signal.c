/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 17:17:23 by memartin          #+#    #+#             */
/*   Updated: 2020/07/16 22:40:35 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ignore_signal(t_minishell *data)
{
	data->signal_set = 1;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	test_func(int signum)
{
	if (signum == SIGINT)
	{
		g_signum = SIGINT;
		ft_putstr_fd("\n", 2);
	}
	else if (signum == SIGQUIT)
	{
		g_signum = SIGQUIT;
		ft_putstr_fd("Quit\n", 2);
	}
}

void	restore_signals_in_child(t_minishell *data)
{
	g_signum = 0;
	if (data->signal_set)
	{
		signal(SIGINT, test_func);
		signal(SIGQUIT, test_func);
	}
}
