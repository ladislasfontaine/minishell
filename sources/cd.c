/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 19:34:32 by lafontai          #+#    #+#             */
/*   Updated: 2020/06/23 17:37:08 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		change_directory(char *path)
{
	// si pas de path use $HOME
	// si path == "-" use $OLDPWD
	// gérer le cas ou une des 2 variables est unset
	path = remove_spaces(path);
	path = dup_first_word(path);
	if (chdir(path) == -1)
	{
		ft_printf("%s\n", strerror(errno));
		free(path);
		return (-1);
	}
	free(path);
	return (0);
}
