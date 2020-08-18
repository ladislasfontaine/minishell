/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 11:02:04 by lafontai          #+#    #+#             */
/*   Updated: 2020/08/18 11:43:27 by memartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		remove_redirection_1(t_command *cmd, char **tab, int k)
{
	tab[k] = 0;
	free_tab(cmd->args);
	cmd->args = tab;
}

void			remove_redirection(t_minishell *data, t_command *cmd, int i)
{
	char	**tab;
	int		j;
	int		k;

	j = 0;
	while (cmd->args[j])
		j++;
	if (!(tab = (char **)malloc(sizeof(char *) * (j - 1))))
	{
		data->stop = 1;
		return ;
	}
	j = 0;
	k = 0;
	while (cmd->args[j])
	{
		if (j != i && j != i + 1)
		{
			tab[k] = ft_strdup(cmd->args[j]);
			k++;
		}
		j++;
	}
	remove_redirection_1(cmd, tab, k);
}

int				create_redirection
	(t_minishell *data, t_command *cmd, int i, int flags)
{
	int		fd;

	if ((fd = open(cmd->args[i + 1], flags, 0644)) < 0)
	{
		print_error_exec_errno(cmd->args[i + 1], strerror(errno));
		data->stop = 1;
	}
	if ((ft_strequ(cmd->args[i], ">") ||
		ft_strequ(cmd->args[i], ">>")) && cmd->out)
		close(cmd->out);
	if (ft_strequ(cmd->args[i], "<") && cmd->in)
		close(cmd->in);
	remove_redirection(data, cmd, i);
	return (fd);
}

static int		redirection_router_norm
	(t_minishell *data, t_command *cmd, int i)
{
	if (cmd->args[i] && !cmd->args[i + 1] && !cmd->was_in_quote[i])
	{
		if (check_first_chevron(data, cmd->args[i]))
			return (0);
	}
	if (cmd->out == -1 || cmd->in == -1)
		return (0);
	return (1);
}

int				redirection_router(t_minishell *data, t_command *cmd)
{
	int		i;

	i = 0;
	while (cmd->args[i] && cmd->args[i + 1])
	{
		cmd->nb_arg = i;
		if (parse_chevron(data, cmd, cmd->args[i], cmd->args[i + 1]))
			return (0);
		if (ft_strequ(cmd->args[i], ">") && cmd->out != -1 &&
			!cmd->was_in_quote[i])
			cmd->out = create_redirection(data, cmd, i,
			O_TRUNC | O_RDWR | O_CREAT);
		else if (ft_strequ(cmd->args[i], ">>") && cmd->out != -1 &&
			!cmd->was_in_quote[i])
			cmd->out = create_redirection(data, cmd, i,
			O_RDWR | O_CREAT | O_APPEND);
		else if (ft_strequ(cmd->args[i], "<") && cmd->in != -1 &&
			!cmd->was_in_quote[i])
			cmd->in = create_redirection(data, cmd, i, O_RDONLY);
		else
			i++;
	}
	return (redirection_router_norm(data, cmd, i));
}
