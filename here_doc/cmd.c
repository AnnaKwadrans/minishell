/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 00:33:55 by kegonza           #+#    #+#             */
/*   Updated: 2025/05/23 00:34:03 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"

t_cmd	*get_heredoc_cmd(char *line, t_heredoc *here_doc)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->heredoc = here_doc;
	if (!cmd->heredoc)
		return (NULL);
	while (line[i] != '\0')
	{
		if (line[i] == '<' && line[i + 1] == '<')
			break ;
		i++;
	}
	cmd->infile = ft_substr(line, 0, i);
	cmd->outfile = NULL;
	cmd->args = NULL;
	cmd->fd_in = -1;
	cmd->fd_out = -1;
	return (cmd);
}
