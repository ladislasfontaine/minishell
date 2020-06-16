/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 19:24:13 by lafontai          #+#    #+#             */
/*   Updated: 2020/06/16 19:38:56 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cwd(void)
{
	char	buff[CMD_SIZE];

	getcwd(buff, CMD_SIZE);
	// check si la fonction return null on doit augmenter la taille du buffer
	ft_printf("%s\n", buff);
}
