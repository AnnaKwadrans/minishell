/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:50:49 by akwadran          #+#    #+#             */
/*   Updated: 2025/07/28 15:05:39 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "echo", 4) == 0 || ft_strncmp(cmd, "cd", 2) == 0
		|| ft_strncmp(cmd, "env", 3) == 0 || ft_strncmp(cmd, "pwd", 3) == 0
		|| ft_strncmp(cmd, "export", 6) == 0 || ft_strncmp(cmd, "unset", 5) == 0
		|| ft_strncmp(cmd, "exit", 4) == 0)
		return (1);
	else
		return (0);
}

int	save_stdfds(t_cmd *cmd, int *saved_stdin, int *saved_stdout)
{
	if (cmd->infile || cmd->heredoc)
	{
		*saved_stdin = dup(STDIN_FILENO);
		if (*saved_stdin == -1)
			return (ft_putendl_fd("saved_stdin redir err", 2), 1);
	}
	if (cmd->outfile)
	{
		*saved_stdout = dup(STDOUT_FILENO);
		if (*saved_stdout == -1)
		{
			if (cmd->infile || cmd->heredoc)
			{
				dup2(*saved_stdin, STDIN_FILENO);
				close(*saved_stdin);
			}
			return (ft_putendl_fd("saved_stdout redir err", 2), 1);
		}
	}
	return (0);
}

void	restore_stdfds(t_cmd *cmd, int *saved_stdin, int *saved_stdout)
{
	if (cmd->infile || cmd->heredoc)
	{
		dup2(*saved_stdin, STDIN_FILENO);
		close(*saved_stdin);
	}
	if (cmd->outfile)
	{
		dup2(*saved_stdout, STDOUT_FILENO);
		close(*saved_stdout);
	}
}

int	exec_builtin(t_cmd *cmd, int pipes, int *fds, int i)
{
	int	saved_stdin;
	int	saved_stdout;

	/*	
	if (cmd->infile || cmd->heredoc)
	{
		saved_stdin = dup(STDIN_FILENO);
		if (saved_stdin == -1)
			return (ft_putendl_fd("saved_stdin redir err", 2), 1);
	}
	if (cmd->outfile)
	{
		saved_stdout = dup(STDOUT_FILENO);
		if (saved_stdout == -1)
		{
			if (cmd->infile || cmd->heredoc)
			{
				dup2(saved_stdin, STDIN_FILENO);
				close(saved_stdin);
			}
			return(ft_putendl_fd("saved_stdout redir err", 2), 1);
		}
	}
	*/
	if (save_stdfds(cmd, &saved_stdin, &saved_stdout) > 0)
		return (1);
	close_fds(fds, pipes, (i - 1) * 2, (i * 2) + 1);
	if (redirect(cmd, pipes, fds, i) != 0)
	{
		ft_putendl_fd("redir err", 2);
		if (cmd->infile || cmd->heredoc)
		{
			dup2(saved_stdin, STDIN_FILENO);
			close(saved_stdin);
		}
		if (cmd->outfile)
		{
			dup2(saved_stdout, STDOUT_FILENO);
			close(saved_stdout);
		}
		return (1);
	}
	ft_builtin(cmd);
	/*
	if (cmd->infile || cmd->heredoc)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
	if (cmd->outfile)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
	*/
	restore_stdfds(cmd, &saved_stdin, &saved_stdout);
	return (cmd->p_status);
}

int	ft_builtin(t_cmd *cmd)
{
	if (ft_strncmp(cmd->args[0], "echo", 4) == 0)
		cmd->p_status = ft_echo(cmd->data, cmd->args);
	else if (ft_strncmp(cmd->args[0], "cd", 2) == 0)
		cmd->p_status = ft_cd(cmd->data, cmd->args);
	else if (ft_strncmp(cmd->args[0], "env", 3) == 0)
		cmd->p_status = ft_env(cmd->data->vars);
	else if (ft_strncmp(cmd->args[0], "pwd", 3) == 0)
		cmd->p_status = ft_pwd();
	else if (ft_strncmp(cmd->args[0], "export", 6) == 0)
		cmd->p_status = ft_export(cmd->data, cmd->data->vars, cmd->args);
	else if (ft_strncmp(cmd->args[0], "unset", 5) == 0)
		cmd->p_status = ft_unset(cmd->args, cmd->data);
	else if (ft_strncmp(cmd->args[0], "exit", 4) == 0)
	{
		//printf("CHECK EXIT\n");
		cmd->p_status = ft_exit(cmd->data, cmd->args);
	}
	cmd->data->last_status = cmd->p_status;
	//ft_putendl_fd(ft_itoa(cmd->data->last_status), 2);
	return (cmd->data->last_status);
}
