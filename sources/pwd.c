/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 19:24:13 by lafontai          #+#    #+#             */
/*   Updated: 2020/07/16 16:28:56 by memartin         ###   ########.fr       */
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
			ft_printf("minishell: pwd: %s\n", strerror(errno));
	}
	else
		ft_printf("%s\n", buff);
	return (0);
}

int		command_pwd(t_minishell *data, t_command *cmd)
{
	char		*pwd;

	data->exit = 0;
	if (cmd->args[1] && cmd->args[1][0] == '-' && cmd->args[1][1])
	{
		data->exit = 1;
		ft_printf("minishell: pwd: %s: invalid option\n", cmd->args[1]);
		return (-1);
	}
	pwd = get_var_value(data, "PWD");
	ft_printf("%s\n", pwd);
	free(pwd);
	return (0);
}

char	*return_cwd(void)
{
	char	*buff;
	int		size;
	int		i;

	size = CMD_SIZE;
	buff = NULL;
	i = 1;
	while (!buff)
	{
		errno = 0;
		if (!(buff = ft_strnew(size * i)))
			return (NULL);
		if (!getcwd(buff, size * i) && errno == ERANGE)
		{
			free(buff);
			buff = NULL;
		}
		else if (errno != 0)
		{
			free(buff);
			return (NULL);
		}
		i++;
	}
	return (buff);
}
