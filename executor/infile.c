/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:43:42 by akwadran          #+#    #+#             */
/*   Updated: 2025/07/12 17:44:15 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	handle_infile(t_cmd *cmd, t_data *data)
{
	if (cmd->heredoc)
		return (0);
	else
	{
		if (check_infile(cmd->infile, data) == -1)
			return (-1);
		if (open_infile(cmd, data) == -2)
			return (-2);
	}
	return (0);
}

int	check_infile(char **infile, t_data *data)
{
	int	i;

	i = 0;
	while (infile[i])
	{
		if (access(infile[i], F_OK) == -1)
		{
			perror("No such file");
			data->last_status = 1;
			return (-1);
		}
		if (access(infile[i], R_OK) == -1)
		{
			perror("Permission denied");
			data->last_status = 1;
			return (-1);
		}
		i++;
	}
	return (0);
}

int	open_infile(t_cmd *cmd, t_data *data)
{
	int	i;

	i = 0;
	while (cmd->infile[i])
	{
		if (cmd->fd_in != STDIN_FILENO)
			close(cmd->fd_in);
		cmd->fd_in = open(cmd->infile[i], O_RDONLY);
		if (cmd->fd_in == -1)
		{
			perror("Open failed");
			data->last_status = 1;
			return (-2);
		}
		i++;
	}
	return (0);
}
