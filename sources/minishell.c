/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 11:41:09 by lafontai          #+#    #+#             */
/*   Updated: 2020/06/22 18:14:00 by lafontai         ###   ########.fr       */
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

int		create_command(t_minishell *data, int start, int end)
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

int		line_split(t_minishell *data)
{
	int			old_i;
	int			i;

	i = 0;
	old_i = 0;
	while (data->line[i])
	{
		check_quotes(data->line[i], &data->s_quote, &data->d_quote);
		if ((data->line[i] == '|' || data->line[i] == ';')
			&& !data->s_quote && !data->d_quote)
		{
			if (data->line[i] == '|')
				data->separator = PIPE;
			if (data->line[i] == ';')
				data->separator = SEMI_COLON;
			create_command(data, old_i, i);
			old_i = i + 1;
		}
		i++;
	}
	create_command(data, old_i, i - 1);
	return (0);
}

int		get_line(char **line)
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

void	set_prompt(t_minishell *data)
{
	while (data->run)
	{
		ft_printf("minishell$ ");
		data->line = ft_strnew(1);
		get_line(&data->line);
		line_split(data);
		line_iteration(data);
		reset_command(data);
	}
}

int		main(int argc, char **argv, char **envp)
{
	t_minishell	data;

	(void)argc;
	(void)argv;
	init_minishell(&data);
	init_env(&data, envp);
	set_prompt(&data);
	return (0);
}
