/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:40:21 by akwadran          #+#    #+#             */
/*   Updated: 2025/07/28 14:59:35 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	handle_outfile(t_cmd *cmd, t_data *data)
{
	int	fd;

	if (check_outfile(cmd->outfile, data) == -1)
		return (-1);
	if (open_outfile(cmd, data) == -2)
		return (-2);
	return (0);
}

int	check_outfile(char **outfile, t_data *data)
{
	int	i;

	i = 0;
	while (outfile && outfile[i])
	{
		if ((access(outfile[i], F_OK) == 0 && access(outfile[i], W_OK) == -1))
		{
			perror("Permission denied");
			data->last_status = 1;
			return (-1);
		}
		i++;
	}
	return (0);
}

int	open_outfile(t_cmd *cmd, t_data *data)
{
	int	i;

	i = 0;
	while (cmd->outfile[i])
	{
		if (cmd->fd_out != STDOUT_FILENO)
			close(cmd->fd_out);
		if (cmd->append)
			cmd->fd_out = open(cmd->outfile[i], O_WRONLY | O_CREAT
					| O_APPEND, 0644);
		else
			cmd->fd_out = open(cmd->outfile[i], O_WRONLY | O_CREAT
					| O_TRUNC, 0644);
		if (cmd->fd_out == -1)
		{
			perror("Open failed");
			data->last_status = 1;
			return (-1);
		}
		i++;
	}
	return (0);
}
