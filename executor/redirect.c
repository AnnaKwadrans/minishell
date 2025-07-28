/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:33:29 by akwadran          #+#    #+#             */
/*   Updated: 2025/07/26 21:31:37 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	redirect(t_cmd *cmd, int pipes, int *fds, int i)
{
	//printf("***REDIRECTING %d***\n", i);
	//printf("cmd %d, pipes %d\n", i, pipes);
	//if (fds)
	//	printf("in pipe: %d - out pipe: %d\n", fds[(i - 1) * 2], fds[(i * 2) + 1]);
	//if (handle_infile(cmd, cmd->data) != 0)
	//	return (1);
	//if (handle_outfile(cmd, cmd->data) != 0)
	//	return (1);
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
		//printf("REDIRECTING INFILE\n");
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
		//printf("REDIRECTING IN PIPE\n");
		if (dup2(fds[(i - 1) * 2], STDIN_FILENO) < 0)
			perror("dup2 pipe input");
		close(fds[(i - 1) * 2]);
	}
	return (0);
}

int	redirect_output(t_cmd *cmd, int pipes, int *fds, int i)
{
	if (cmd->outfile)
	{
		//printf("REDIRECTING OUTFILE\n");
		if (i != pipes)
			close(fds[(i * 2) + 1]);
		if (handle_outfile(cmd, cmd->data) != 0)
			return (1);
		if (dup2(cmd->fd_out, STDOUT_FILENO) < 0)
			perror("dup2 outfile");
		close(cmd->fd_out);
	}
	else if (i != pipes)
	{
		//printf("REDIRECTING OUT PIPE\n");
		if (dup2(fds[(i * 2) + 1], STDOUT_FILENO) < 0)
			perror("dup2 pipe output");
		//printf("%d; FD %d\n", i, fds[(i * 2) + 1]);
		close(fds[(i * 2) + 1]);
	}
	return (0);
}
