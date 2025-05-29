/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 00:33:55 by kegonza           #+#    #+#             */
/*   Updated: 2025/05/27 19:28:55 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"

static void	setup_heredoc_input(t_cmd *cmd)
{
	int	pipefd[2];
	int	i;

	i = 0;
	pipe(pipefd);
	while (cmd->heredoc->buffer[i])
	{
		write(pipefd[1], cmd->heredoc->buffer[i],
			strlen(cmd->heredoc->buffer[i]));
		write(pipefd[1], "\n", 1);
		i++;
	}
	close(pipefd[1]);
	cmd->fd_in = pipefd[0]; // lo usará en fork_and_exec
}

static void	default_assign_cmd(t_cmd *cmd)
{
	cmd->args = malloc(sizeof(char *) * 2);
	if (!cmd->args)
		return (free_cmd(cmd));
	cmd->args[0] = ft_strdup("cat");
	cmd->args[1] = NULL;
	setup_heredoc_input(cmd);
	return ;
}
void	get_heredoc_cmd(char *line, t_cmd *cmd)
{
	int		i;
	char	*args;

	args = NULL;
	i = 0;
	while (line[i] && line[i] != '<') // o buscar "<<"
		i++;
	args = ft_substr(line, 0, i);
	if (!args)
		default_assign_cmd(cmd);
	else
	{
		cmd->args = ft_split(args, ' ');
		free(args);
		if (!cmd->args)
			return (free_cmd(cmd));
	}
	// if (cmd->heredoc->buffer)
	setup_heredoc_input(cmd);
	cmd->fd_out = STDOUT_FILENO;
	cmd->outfile = NULL;
	cmd->append = 0;
	cmd->infile = NULL; // porque no hay archivo como tal
	cmd->delimit = NULL;
	cmd->pid = 0;
	cmd->p_status = 0;
}
