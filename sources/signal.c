/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 17:17:23 by memartin          #+#    #+#             */
/*   Updated: 2020/06/25 17:25:30 by memartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ignore_signal(t_minishell *data)
{
	data->signal_set = 1;
	
	// ignore "Ctrl-C"
    SIGINT_handler = signal(SIGINT, SIG_IGN);
	// ignore "Ctrl-\"
    SIGQUIT_handler = signal(SIGQUIT, SIG_IGN);
}

void restore_signals_in_child(t_minishell *data)
{
	if (data->signal_set)
	{	
		signal(SIGINT, SIGINT_handler);
		signal(SIGQUIT, SIGINT_handler);
	}
}
