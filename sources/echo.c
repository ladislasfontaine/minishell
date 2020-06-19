/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 14:09:09 by lafontai          #+#    #+#             */
/*   Updated: 2020/06/19 15:30:37 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

	// OK manage single and double quotes
	// OK manage special characters and escapes
	// replace variables if any (depending on quotes)
	// OK print all the strings separated by one space
	// OK option -n to manage -> no trailing new line
	// if pipe the string will be sent to stdin of next command

void	get_output(t_minishell *data, t_command *cmd, char **output, char *str)
{
	int		i;
	int		j;

	(void)data;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' && cmd->s_quote == 0 && cmd->d_quote != 1)
			cmd->s_quote = 1;
		else if (str[i] == '\'' && cmd->s_quote == 1)
			cmd->s_quote = 0;
		else if (str[i] == '\"' && cmd->d_quote == 0  && cmd->s_quote != 1)
			cmd->d_quote = 1;
		else if (str[i] == '\"' && cmd->d_quote == 1)
			cmd->d_quote = 0;
		else if (!(str[i] == '\\' && !cmd->d_quote && !cmd->s_quote))
		{
			(*output)[j] = str[i];
			j++;
			if (str[i] == ' ' && !cmd->d_quote && !cmd->s_quote)
			{
				while (str[i] && str[i] == ' ')
					i++;
				continue ;
			}
		}
		i++;
	}
}

void	command_echo(t_minishell *data, t_command *cmd, char *str)
{
	char	*output;
	int		option;

	(void)data;
	(void)cmd;
	str = remove_spaces(str);
	if (!*str)
	{
		ft_printf("\n");
		return ;
	}
	option = (!ft_strncmp(str, "-n ", 3) || !ft_strcmp(str, "-n")) ? 1 : 0;
	if (option)
		str += 2;
	str = remove_spaces(str);
	// change size
	if (!(output = ft_strnew(CMD_SIZE)))
		exit_error(data);
	get_output(data, cmd, &output, str);
	if (!option)
		ft_printf("%s\n", output);
	else
		ft_printf("%s", output);
	free(output);
}
