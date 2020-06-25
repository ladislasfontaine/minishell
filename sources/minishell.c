/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 11:41:09 by lafontai          #+#    #+#             */
/*   Updated: 2020/06/25 17:18:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	make a main struct minishell to store all the data
	make an error function to clear command and make a new prompt if malloc fail

	1/ create a prompt (minishell$) and wait
	2/ when enter is pressed get the command to parse
	3/ routing toward the right function based on the command
	4/ do the action (or error message)
		- replace variables
		- split commands if multiple with pipes
	5/ come back to the prompt (unless it was exit)
*/

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

static void			split_all_command(t_minishell *data)
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
}

static t_command	*get_last_command(t_minishell *data)
{
	t_command	*cmd;
	t_list		*element;

	element = data->cmd;
	while (element->next)
		element = element->next;
	cmd = (t_command*)element->content;
	return (cmd);
}

static void			set_prompt(t_minishell *data)
{
	while (data->run)
	{
		ft_printf(""GREEN"➜  "CYAN"minishell "RESET"");
		data->line = ft_strnew(1);
		get_line(&data->line);
		if (ft_strlen(data->line) > 1)
		{
			split_line(data);
			split_all_command(data);
			if (!command_router_no_process(data, get_last_command(data)))
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
