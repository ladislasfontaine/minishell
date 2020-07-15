/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 11:41:09 by lafontai          #+#    #+#             */
/*   Updated: 2020/07/15 18:39:17 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int					create_command(t_minishell *data, int start, int end)
{
	t_command	*command;
	t_list		*previous;
	t_list		*new;
	int			len;

	command = NULL;
	previous = ft_lstlast(data->cmd);
	len = (end - start) < 0 ? 0 : (end - start);
	if (init_command(&command, data->separator, ft_substr(data->line, start, len), previous) == -1)
		return (-1);
	new = ft_lstnew((void *)command);
	ft_lstadd_back(&data->cmd, new);
	data->separator = 0;
	return (0);
}

static int			get_line(char **line)
{
	char		*buff;
	int			rd;

	if (!line)
		return (-1);
	rd = CMD_SIZE;
	while (rd == CMD_SIZE)
	{
		buff = ft_strnew(CMD_SIZE + 1);
		rd = read (0, buff, CMD_SIZE);
		if (rd < 0)
		{
			free(buff);
			return (-1);
		}
		buff[rd] = '\0';
		*line = ft_joinfree(*line, buff);
	}
	return (1);
}

static int			split_all_command(t_minishell *data)
{
	t_list		*element;
	t_command	*cmd;

	element = data->cmd;
	while (element)
	{
		cmd = (t_command*)element->content;
		replace_variables(data, cmd);
		split_command(cmd);
		redirection_router(data, cmd);
		element = element->next;
	}
	element = data->cmd;
	while (element)
	{
		cmd = (t_command*)element->content;
		if (!cmd->args[0] && ((cmd->previous && cmd->previous->separator == PIPE)
			|| cmd->separator == PIPE))
		{
			ft_putstr_fd("parse error near '|'\n", 2);
			return (0);
		}
		element = element->next;
	}
	return (1);
}

int					process_command(t_minishell *data, t_list *element)
{
	t_command	*cmd;

	cmd = (t_command*)element->content;
	replace_variables(data, cmd);
	split_command(cmd);
	redirection_router(data, cmd);
	if (!cmd->args[0] && ((cmd->previous && cmd->previous->separator == PIPE)
		|| cmd->separator == PIPE))
	{
		ft_putstr_fd("parse error near '|'\n", 2);
		return (0);
	}
	return (1);
}

static void			set_prompt(t_minishell *data)
{
	while (data->run)
	{
		ft_putstr_fd(""GREEN"➜  "CYAN"minishell "RESET"", 2);
		data->line = ft_strnew(1);
		get_line(&data->line);
		if (ft_strlen(data->line) > 1)
		{
			split_line(data);
			if (split_all_command(data))
				line_iteration(data);
		}
		else if (!ft_strlen(data->line))
			exit_normal(data);
		reset_command(data);
	}
}

int					main(int argc, char **argv, char **envp)
{
	t_minishell	data;

	(void)argc;
	(void)argv;
	init_minishell(&data);
	ignore_signal(&data);
	init_env(&data, envp);
	set_prompt(&data);
	return (0);
}
