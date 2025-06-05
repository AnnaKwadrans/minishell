/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:46:59 by akwadran          #+#    #+#             */
/*   Updated: 2025/06/05 00:32:19 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"
#include "../data.h"
#include "../libft/libft.h"

void	clean_data_program(t_data *data)
{
	int	i;
	int	j;

	free_line(data->line);
	data->line = NULL;
	if (data->cmds)
	{
		i = 0;
		while (data->cmds[i])
		{
			j = 0;
			while (data->cmds[i][j])
			{
				free_cmd(data->cmds[i][j]);
				j++;
			}
			free(data->cmds[i]);
			i++;
		}
		free(data->cmds);
		data->cmds = NULL;
	}
	free_array(data->part_lines);
	data->part_lines = NULL;
	if (data->pipes)
	{
		free(data->pipes);
		data->pipes = NULL;
	}
}

void	free_data(t_data *data)
{
	//free_history(data->history_lines); // por hacer la funcion
	clean_data_program(data);
}

void	free_cmd(t_cmd	*cmd)
{
	if (!cmd)
		return ;
	free_array(cmd->args);
	if (cmd->infile)
	{
		free(cmd->infile);
		cmd->infile = NULL;
	}
	if (cmd->outfile)
	{
		free(cmd->outfile);
		cmd->outfile = NULL;
	}
	if (cmd->delimit)
	{
		free(cmd->delimit);
		cmd->delimit = NULL;
	}
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
