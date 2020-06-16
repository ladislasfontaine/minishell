/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 11:41:09 by lafontai          #+#    #+#             */
/*   Updated: 2020/06/16 14:47:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	parser la commande pour remplacer les variables s'il y en a
	est-ce que $(commande) est possible ?
	gérer les \ + caractère spécial
	redirections à gérer mais que vers un fichier avec une path (pas vers un fd)
*/

#include "minishell.h"

int		get_commande(char **line)
{
	char		*buff;
	int			rd;

	if (!line)
		return (-1);
	rd = 1;
	while (rd > 0)
	{
		buff = ft_strnew(512 + 1);
		rd = read (0, buff, 512);
		buff[rd] = '\0';
		*line = ft_joinfree(*line, buff);
	}
	return (1);
}


void	set_prompt(void)
{
	int		done;
	char 	*line;

	done = 1;
	while (done)
	{
		ft_printf(">");
		line = ft_strnew(1);
		get_commande(&line);
		ft_printf("cmd :%s\n", line);
		free(line);
	}
}

int		main(void)
{
	set_prompt();
	return (0);
}
