/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 19:24:13 by lafontai          #+#    #+#             */
/*   Updated: 2020/06/17 09:04:11 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		call_getcwd(int size)
{
	char	*buff;

	errno = 0;
	if (!(buff = ft_strnew(size)))
		return (-1);
	if (!getcwd(buff, size))
	{
		if (errno == ERANGE)
		{
			free(buff);
			return (-2);
		}
		else
			ft_printf("%s\n", strerror(errno));
	}
	else
		ft_printf("%s\n", buff);
	return (0);
}

int		print_cwd(void)
{
	int		i;
	int		ret;

	i = 1;
	while ((ret = call_getcwd(CMD_SIZE * i)) == -2)
		i++;
	if (ret == -1)
		return (-1);
	return (0);
}
