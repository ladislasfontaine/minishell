/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 19:34:32 by lafontai          #+#    #+#             */
/*   Updated: 2020/06/17 09:40:59 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		change_directory(char *path)
{
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
