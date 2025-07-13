/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:50:49 by akwadran          #+#    #+#             */
/*   Updated: 2025/07/12 17:52:39 by akwadran         ###   ########.fr       */
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

int	exec_builtin(t_cmd *cmd, int pipes, int *fds, int i)
{
	int	saved_stdin;
	int	saved_stdout;

	if (cmd->data->pipes == 0)
	{
		saved_stdin = dup(STDIN_FILENO);
		saved_stdout = dup(STDOUT_FILENO);
		close_fds(fds, pipes, (i - 1) * 2, (i * 2) + 1);
		if (redirect(cmd, pipes, fds, i) != 0)
			return (1);
		ft_builtin(cmd);
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
	else
		child(cmd, pipes, fds, i);
	return (0);
}

void	ft_builtin(t_cmd *cmd)
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
		ft_exit(cmd->data, cmd->args);
	cmd->data->last_status = cmd->p_status;
	return ;
}
