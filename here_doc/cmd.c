/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonzal <kegonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 00:33:55 by kegonza           #+#    #+#             */
/*   Updated: 2025/07/28 20:59:42 by kegonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"

static void	setup_heredoc_input(t_cmd *cmd)
{
	int			i;
	t_heredoc	*here_doc;

	here_doc = cmd->heredoc;
	if (pipe(here_doc->pipesfd) == -1)
		return (perror("pipe"), free_cmd(cmd));
	cmd->fd_in = here_doc->pipesfd[0];
	if (!cmd->heredoc || !cmd->heredoc->buffer || !cmd->heredoc->buffer[0])
	{
		close(here_doc->pipesfd[1]);
		return ;
	}
	i = 0;
	while (cmd->heredoc->buffer[i])
	{
		write(here_doc->pipesfd[1], cmd->heredoc->buffer[i],
			ft_strlen(cmd->heredoc->buffer[i]));
		write(here_doc->pipesfd[1], "\n", 1);
		i++;
	}
	close(here_doc->pipesfd[1]);
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

static char	*get_arg(char *line, t_cmd *cmd)
{
	int		i;
	int		start;
	char	*args;
	char	*trim;

	i = 0;
	while (line[i] && (line[i] == ' ') || (line[i] == '\t'))
		i++;
	start = i;
	while (line[i] && line[i] != '<')
		i++;
	args = ft_substr(line, start, i - start);
	if (args)
	{
		trim = ft_strtrim(args, " \t");
		free(args);
		args = trim;
	}
	return (args);
}

void	get_heredoc_cmd(char *line, t_cmd *cmd)
{
	char	*args;
	int		i;

	args = get_arg(line, cmd);
	if (!args || !args[0])
	{
		if (args)
			free(args);
		default_assign_cmd(cmd);
	}
	else
	{
		cmd->args = ft_split(args, ' ');
		free(args);
		if (!cmd->args)
			return (free_cmd(cmd));
	}
	setup_heredoc_input(cmd);
	cmd->fd_out = STDOUT_FILENO;
	cmd->append = 0;
	cmd->outfile = outfile_heredoc(line, cmd);
	cmd->infile = NULL;
	cmd->pid = 0;
	cmd->p_status = 0;
}
