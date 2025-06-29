/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:46:59 by akwadran          #+#    #+#             */
/*   Updated: 2025/06/29 13:48:49 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../data.h"
#include "../libft/libft.h"

void	free_vars(void *args);

void	free_here_doc(t_heredoc *here_doc)
{
	if (here_doc)
	{
		if (here_doc->delimiter)
			free(here_doc->delimiter);
		if (here_doc->buffer)
			free_array(here_doc->buffer);
		free(here_doc);
	}
}

void	clean_data_program(t_data *data)
{
	int	i;

	if (!data)
		return ;
	if (data->line)
	{
		free_line(data->line);
		data->line = NULL;
	}
	if (data->cmds)
	{
		free_cmds(data);
		/*
		i = 0;
		while (data->cmds[i])
		{
			printf("freeing cdm %d\n", i);
			free_cmd(data->cmds[i]);
			//free(data->cmds[i]);
			data->cmds[i] = NULL;
			i++;
		}
		free(data->cmds);
		data->cmds = NULL;
	}
	data->pipes = 0;
	if (data->fds)
	{
		free(data->fds);
		data->fds = NULL;
	}
	// free_array(data->part_lines);
	// data->part_lines = NULL;
}

void	free_data(t_data *data)
{
	//free_history(data->history_lines); // por hacer la funcion
	if (!data)
		return ;
	clean_data_program(data);
	if (data->vars)
	{
		free_data(data->vars);
		data->vars = NULL;
	}
}

void	free_cmds(t_data *data)
{
	int	i;

	i = 0;
	while (data->cmds[i])
	{
		free_cmd(data->cmds[i]);
		data->cmds[i] = NULL;
		i++;
	}
	free(data->cmds);
	data->cmds = NULL;
}

void	free_cmd(t_cmd	*cmd)
{
	if (!cmd)
		return ;
	free_array(cmd->args);
	cmd->args = NULL;
	if (cmd->infile)
	{
		free_array(cmd->infile);
		cmd->infile = NULL;
	}
	if (cmd->outfile)
	{
		free_array(cmd->outfile);
		cmd->outfile = NULL;
	}
	if (cmd->heredoc)
	{
		free_here_doc(cmd->heredoc);
		cmd->heredoc = NULL;
	}
	//if (cmd->delimit)
	//{
	//	free(cmd->delimit);
	//	cmd->delimit = NULL;
	//}
	cmd->data = NULL;
	free(cmd);
	cmd = NULL;
}

void	free_line(t_lines *line)
{
	if (!line)
		return ;
	if (line->line)
	{
		free(line->line);
		line->line = NULL;
	}
	free(line);
	line = NULL;
}

