/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:46:59 by akwadran          #+#    #+#             */
/*   Updated: 2025/06/21 14:37:40 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"
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
	int	j;

	if (!data)
		return ;
	if (data->line)
		free_line(data->line);
	if (data->cmds)
	{
		i = 0;
		while (data->cmds[i])
		{
			free_cmd(data->cmds[i]);
			i++;
		}
		free(data->cmds);
		data->cmds = NULL;
	}
	if (data->history_lines)
	{
		free_line(data->history_lines);
		data->history_lines = NULL;
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

void	free_data_vars(t_vars *vars)
{
	t_vars	*next;

	while (vars)
	{
		free(vars->name);
		vars->name = NULL;
		free(vars->value);
		vars->value = NULL;
		vars->data = NULL;
		vars = vars->next;
	}
}

void	free_data(t_data *data)
{
	//free_history(data->history_lines); // por hacer la funcion
	clean_data_program(data);
	if (data->vars)
	{
		free_data_vars(data->vars);
		data->vars = NULL;
	}
	if (data->line)
	{
		free_line(data->line);
		data->line = NULL;
	}
}

void	free_cmd(t_cmd	*cmd)
{
	if (!cmd)
		return ;
	free_array(cmd->args);
	if (cmd->infile)
		free_array(cmd->infile);
	if (cmd->outfile)
		free_array(cmd->outfile);
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
