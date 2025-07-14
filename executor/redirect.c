/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:33:29 by akwadran          #+#    #+#             */
/*   Updated: 2025/07/14 18:43:12 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	redirect(t_cmd *cmd, int pipes, int *fds, int i)
{
	if (redirect_input(cmd, pipes, fds, i) == 1)
		return (1);
	if (redirect_output(cmd, pipes, fds, i) == 1)
		return (1);
	return (0);
}

int	redirect_input(t_cmd *cmd, int pipes, int *fds, int i)
{
	if (cmd->heredoc)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) < 0)
			perror("dup2 heredoc");
		close(cmd->fd_in);
	}
	else if (cmd->infile)
	{
		if (i != 0)
			close(fds[(i - 1) * 2]);
		if (handle_infile(cmd, cmd->data) != 0)
			return (1);
		if (dup2(cmd->fd_in, STDIN_FILENO) < 0)
			perror("dup2 pipe infile");
		close(cmd->fd_in);
	}
	else if (i != 0)
	{
		dup2(fds[(i - 1) * 2], STDIN_FILENO); // 0:-2 1:0, 2:2, 3:4 
		close(fds[(i - 1) * 2]);
	}
	return (0);
}

int	redirect_output(t_cmd *cmd, int pipes, int *fds, int i)
{
	// 1) Redirección a fichero
	if (cmd->outfile)
	{
		if (i != pipes)
			close(fds[(i * 2) + 1]);
		if (handle_outfile(cmd, cmd->data) != 0)
			return (1);
		if (dup2(cmd->fd_out, STDOUT_FILENO) < 0)
			perror("dup2 outfile");
		close(cmd->fd_out);
	}
	// 2) Pipe siguiente
	else if (i != pipes)
	{
		if (dup2(fds[(i * 2) + 1], STDOUT_FILENO) < 0)
			perror("dup2 pipe output");
		close(fds[(i * 2) + 1]);
	}
	return (0);
}

