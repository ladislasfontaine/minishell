/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 14:56:53 by memartin          #+#    #+#             */
/*   Updated: 2020/07/16 16:00:52 by memartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		print_error_exit(char *s)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

void		print_error_fork(char *s)
{
	ft_putstr_fd("minishell: fork: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\n", 2);
}
