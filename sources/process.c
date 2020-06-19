/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 11:03:34 by lafontai          #+#    #+#             */
/*   Updated: 2020/06/19 15:52:49 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// creation d'un nouveau process pour chaque commande à exécuter
	// si séparateur est pipe on fait la redirection avec un processus enfant
	// si pas un pipe on exécute et on ferme le processus
// à la fin d'une suite de pipes on envoit stdout du dernier enfant sur stdout de minishell

void	line_iteration(t_minishell *data)
{
	t_list		*element;

	element = data->cmd;
	while (element)
	{
		create_process(data, element);
		// check for redirections
		while (((t_command *)element->content)->separator == PIPE)
			element = element->next;
		element = element->next;
	}
}

void	create_process(t_minishell *data, t_list *element)
{
	pid_t		cpid;
	t_command	*cmd;
	char		*str;
	int			status;

	cmd = (t_command *)element->content;
	replace_variables(data, cmd);
	str = ft_strtrim(cmd->cmd, " ");
	if (!ft_strncmp(str, "exit ", 5) || !ft_strcmp(str, "exit"))
	{
		ft_strdel(&str);
		exit_normal(data);
	}
	if ((cpid = fork()) == -1)
	{
		ft_printf("%s\n", strerror(errno));
		exit_error(data);
	}
	if (cpid == 0)
	{
		// faire fonction execute_child
		ft_printf("Child PID is %d\n", getpid());
		command_router(data, cmd);
		if (cmd->separator == PIPE)
		{
			create_process(data, element->next);
		}
		exit(0);
		// create child from inside
	}
	else
	{
		// faire fonction execute_parent
		if (waitpid(cpid, &status, WUNTRACED | WCONTINUED) == -1)
			exit_error(data);
		if (WIFEXITED(status))
			ft_printf("Exited child %d\n", (int)cpid);
	}
	while (!WIFEXITED(status) && !WIFSIGNALED(status))
    	exit_normal(data);
}
