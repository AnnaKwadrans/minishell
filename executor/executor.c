/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 19:02:46 by akwadran          #+#    #+#             */
/*   Updated: 2025/07/02 21:43:47 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../data.h"
#include "../parser/parser.h"
#include "executor.h"
#include "../here_doc/here_doc.h"

int	execute_line(t_data *data)  //t_cmd **cmds, int pipes, int *fds, int *last_status)
{
	int	i;
	int	status;

        if (!data)
		return (-1);
	//printf("pipes: %d\n", pipes);
	if (!data || !data->cmds || !data->cmds[0])
		return (0);
	if (data->pipes > 0)
		data->fds = create_pipes(data->pipes);
	i = 0;
	while (data->cmds[i])
	{
		printf("check cmd %d\n", i);
		handle_cmd(data, data->cmds[i], i);
		/*if (is_builtin(data->cmds[i]->args[0]))
                {
			data->cmds[i]->is_builtin = 1;
                        exec_builtin(data->cmds[i], data->pipes, data->fds, i);
                }
                else
			child(data->cmds[i], data->pipes, data->fds, i);
		*/
		i++;
	}
	close_fds(data->fds, data->pipes, -1, -1);
	if (data->fds)
	{
		free(data->fds);
		data->fds = NULL;
	}
	i = 0;
	while (waitpid(-1, &status, 0) > 0)
		data->last_status = WEXITSTATUS(status);
	//printf("LAST STATUS %d\n", data->last_status);
	return (0);
}

int	*create_pipes(int pipes)
{
	int	*fds;
	int	i;

	//printf("PIPES %d\n", pipes);
	if (pipes == 0)
		return (NULL);
	fds = malloc(sizeof(int) * pipes * 2);
	if (!fds)
		return (NULL);
	i = 0;
	while (i <= pipes)
	{
		//printf("check pipe %d\n", i);
		if (pipe(&fds[i * 2]) < 0)
			return (NULL);
		i++;
	}
	return (fds);
}

int     handle_cmd(t_data *data, t_cmd *cmd, int i)
{
	if (cmd->is_builtin)
	{
		exec_builtin(cmd, data->pipes, data->fds, i);
	}
	else
		child(cmd, data->pipes, data->fds, i);
	return (0); //check
}

void	close_fds(int *fds, int pipes, int wr, int rd)
{
	int	i;

	i = 0;
	while (i < (pipes * 2))
	{
		if (i != wr && i != rd)
			close(fds[i]);
		i++;
	}
}

int	child(t_cmd *cmd, int pipes, int *fds, int i)
{
        //printf("check new %d", i);
        if (!cmd || !cmd->args || !cmd->args[0])
                return (2);
        cmd->pid = fork();
        //printf("check pid: %d\n", cmd->pid);
        if (cmd->pid < 0)
                return (perror("Fork failed"), 2);
        else if (cmd->pid == 0)
        {
                close_fds(fds, pipes, (i - 1) * 2, (i * 2) + 1);
                if (redirect(cmd, pipes, fds, i) != 0)
			return (1);
                //cmd->data->last_cmd = &cmd;

                exec_cmd(cmd);
                exit(cmd->p_status);


		
        }
        else if (cmd->pid > 0)
                return (0);
}
