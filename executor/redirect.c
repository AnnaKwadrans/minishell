/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:33:29 by akwadran          #+#    #+#             */
/*   Updated: 2025/07/28 15:03:33 by akwadran         ###   ########.fr       */
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
			return (perror("dup2 heredoc"), 1);
		close(cmd->fd_in);
	}
	else if (cmd->infile)
	{
		if (i != 0)
			close(fds[(i - 1) * 2]);
		if (handle_infile(cmd, cmd->data) != 0)
			return (1);
		if (dup2(cmd->fd_in, STDIN_FILENO) < 0)
			return (perror("dup2 pipe infile"), 1);
		close(cmd->fd_in);
	}
	else if (i != 0)
	{
		if (dup2(fds[(i - 1) * 2], STDIN_FILENO) < 0)
			return (perror("dup2 pipe input"), 1);
		close(fds[(i - 1) * 2]);
	}
	return (0);
}

int	redirect_output(t_cmd *cmd, int pipes, int *fds, int i)
{
	if (cmd->outfile)
	{
		if (i != pipes)
			close(fds[(i * 2) + 1]);
		if (handle_outfile(cmd, cmd->data) != 0)
			return (1);
		if (dup2(cmd->fd_out, STDOUT_FILENO) < 0)
			return (perror("dup2 outfile"), 1);
		close(cmd->fd_out);
	}
	else if (i != pipes)
	{
		if (dup2(fds[(i * 2) + 1], STDOUT_FILENO) < 0)
			return (perror("dup2 pipe output"), 1);
		close(fds[(i * 2) + 1]);
	}
	return (0);
}

void	redir_err_handler(int *fds, int i, int pipes)
{
	if (i != 0)
		close(fds[(i - 1) * 2]);
	if (i != pipes)
		close(fds[(i * 2) + 1]);
}
