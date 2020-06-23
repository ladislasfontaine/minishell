/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 11:02:04 by lafontai          #+#    #+#             */
/*   Updated: 2020/06/23 17:26:39 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_command(t_command *cmd)
{
	cmd->args = ft_split_special_redir(cmd->cmd, ' ');
}

void	remove_redirection(t_minishell *data, t_command *cmd, int i)
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
	tab[k] = 0;
	free_tab(cmd->args);
	cmd->args = tab;
}

int		create_redirection(t_minishell *data, t_command *cmd, int i, int flags)
{
	int		fd;

	if ((fd = open(cmd->args[i + 1], flags, 0644)) < 0)
	{
		ft_printf("minishell: %s: %s\n", cmd->args[i + 1], strerror(errno));
		data->stop = 1;
	}
	if ((ft_strequ(cmd->args[i], ">") || ft_strequ(cmd->args[i], ">>")) && cmd->out)
		close(cmd->out);
	if (ft_strequ(cmd->args[i], "<") && cmd->in)
		close(cmd->in);
	remove_redirection(data, cmd, i);
	return (fd);
}

void	redirection_router(t_minishell *data, t_command *cmd)
{
	int		i;

	i = 0;
	while (cmd->args[i] && cmd->args[i + 1])
	{
		if (ft_strequ(cmd->args[i], ">") && cmd->out != -1)
			cmd->out = create_redirection(data, cmd, i, O_TRUNC | O_RDWR | O_CREAT);
		else if (ft_strequ(cmd->args[i], ">>") && cmd->out != -1)
			cmd->out = create_redirection(data, cmd, i, O_RDWR | O_CREAT | O_APPEND);
		else if (ft_strequ(cmd->args[i], "<") && cmd->in != -1)
			cmd->in = create_redirection(data, cmd, i, O_RDONLY);
		else
			i++;
	}
}
