/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_synthax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:24:27 by memartin          #+#    #+#             */
/*   Updated: 2020/07/30 16:49:08 by memartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_semi_collon(t_minishell *data)
{
	int			i;
	int			d_quote;
	int			s_quote;

	i = 0;
	d_quote = 0;
	s_quote = 0;
	while (data->line[i])
	{
		check_quotes(data->line[i], &s_quote, &d_quote);
		if (!d_quote && !s_quote && data->line[i] == ';' &&
			data->line[i + 1] == ';')
		{
			print_error_parse_near(";;");
			data->exit = 2;
			return (1);
		}
		i++;
	}
	return (0);
}

int			check_pipe_semi_collon(t_minishell *data)
{
	t_list		*element;
	t_command	*cmd;

	if (check_semi_collon(data))
		return (1);
	element = data->cmd;
	while (element)
	{
		cmd = (t_command*)element->content;
		if (!cmd->args[0] && ((cmd->previous &&
			cmd->previous->separator == PIPE)
			|| cmd->separator == PIPE))
		{
			print_error_parse_near("|");
			data->exit = 2;
			return (1);
		}
		element = element->next;
	}
	return (0);
}

int			check_first_chevron(t_minishell *data, char *arg)
{
	if ((ft_strlen(arg) == 1 && (arg[0] == '>' || arg[0] == '<'))
		|| (ft_strlen(arg) == 2 && (arg[0] == '>' && arg[1] == '>')))
	{
		print_error_parse_near("newline");
		data->exit = 2;
		return (1);
	}
	return (0);
}

int			parse_chevron(t_minishell *data, t_command *cmd,
	char *arg1, char *arg2)
{
	int		len1;
	int		len2;

	len1 = ft_strlen(arg1);
	len2 = ft_strlen(arg2);
	if (cmd->was_in_quote[cmd->nb_arg] || cmd->was_in_quote[cmd->nb_arg + 1])
		return (0);
	if ((len1 == 1 && (arg1[0] == '>' || arg1[0] == '<'))
		|| (len1 == 2 && (arg1[0] == '>' && arg1[1] == '>')))
	{
		if (len2 && (arg2[0] == '>' || arg2[0] == '<'))
		{
			if (len2 > 1 && arg2[0] == '>' && arg2[1] == '>')
				print_error_parse_near(">>");
			else if (len2 && arg2[0] == '>')
				print_error_parse_near(">");
			else if (len2 && arg2[0] == '<')
				print_error_parse_near("<");
			data->exit = 2;
			return (1);
		}
	}
	return (0);
}
