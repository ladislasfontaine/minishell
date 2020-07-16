/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 19:34:32 by lafontai          #+#    #+#             */
/*   Updated: 2020/07/15 18:35:28 by memartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_new_path(t_minishell *data, t_command *cmd)
{
	char	*path;

	if (!cmd->args[1])
		path = get_var_value(data, "HOME");
	else if (ft_strequ(cmd->args[1], "-"))
		path = get_var_value(data, "OLDPWD");
	else
		path = ft_strdup(cmd->args[1]);
	return (path);
}

void	update_variables(t_minishell *data, char *old_path)
{
	char	*temp;
	char	*new_path;
	char	*tab[3];

	tab[0] = NULL;
	tab[1] = NULL;
	tab[2] = NULL;
	if (!(temp = ft_strjoin("OLDPWD=", old_path)))
	{
		free(old_path);
		return ;
	}
	tab[1] = temp;
	ft_export(data, tab);
	free(old_path);
	free(temp);
	if (!(new_path = return_cwd()))
		return ;
	if (!(temp = ft_strjoin("PWD=", new_path)))
	{
		free(new_path);
		return ;
	}
	tab[1] = temp;
	ft_export(data, tab);
	free(new_path);
	free(temp);
}

static void	print_error_cd(char *s1, char *s2, char *err)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(err, 2);
	ft_putstr_fd("\n", 2);
}

int		command_cd(t_minishell *data, t_command *cmd)
{
	char	*path;
	char	*old_path;

	data->exit = 0;
	if (!(path = get_new_path(data, cmd)))
		return (-1);
	if (!(old_path = return_cwd()))
	{
		free(path);
		return (-1);
	}
	if (chdir(path) == -1)
	{
		data->exit = 1;
		print_error_cd(cmd->args[0], cmd->args[1], strerror(errno));
		free(path);
		free(old_path);
		data->exit = 1;
		return (-1);
	}
	free(path);
	update_variables(data, old_path);
	return (0);
}
