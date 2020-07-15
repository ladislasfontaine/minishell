/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 18:07:34 by memartin          #+#    #+#             */
/*   Updated: 2020/07/15 16:22:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		print_error_cmd_not_found(char *s)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void		print_error_parse_near(char *s1)
{
	ft_putstr_fd("parse error near '", 2);
	ft_putstr_fd(s1, 2);
	ft_putstr_fd("'\n", 2);
}

void		print_error_exec_errno(char *s1, char *s2)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd("\n", 2);
}
