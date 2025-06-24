#include "../data.h"
#include "../parser/parser.h"
#include "executor.h"
#include "../here_doc/here_doc.h"

bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "echo", 4) == 0 || ft_strncmp(cmd, "cd", 2) == 0
		|| ft_strncmp(cmd, "env", 3) == 0 || ft_strncmp(cmd, "pwd", 3) == 0
		|| ft_strncmp(cmd, "export", 6) == 0 || ft_strncmp(cmd, "unset", 5) == 0
		|| ft_strncmp(cmd, "exit", 4) == 0 || ft_strncmp(cmd, "mhistory", 8) == 0)
	{
                return (1);
	}
	else
        {
                return (0);
        }
}

int	exec_builtin(t_cmd *cmd, int pipes, int *fds, int i)
{
        //printf("check pid: %d\n", cmd->pid);
        close_fds(fds, pipes, (i - 1) * 2, (i * 2) + 1);
	//redirect(cmd, cmd->data, i);
	if (redirect(cmd, pipes, fds, i) != 0)
		return (1);
        ft_builtin(cmd);
        return (0);
}

void    ft_builtin(t_cmd *cmd)
{
        if (ft_strncmp(cmd->args[0], "echo", 4) == 0)
                cmd->p_status = ft_echo(cmd->data, cmd->args);
        else if (ft_strncmp(cmd->args[0], "cd", 2) == 0)
                cmd->p_status = ft_cd(cmd->data, cmd->args);
        else if (ft_strncmp(cmd->args[0], "env", 3) == 0)
                cmd->p_status = ft_env(cmd->data->vars);
        else if (ft_strncmp(cmd->args[0], "pwd", 3) == 0)
                cmd->p_status = ft_pwd(cmd->args);
        else if (ft_strncmp(cmd->args[0], "export", 6) == 0)
        {
                printf("check ft_builtin\n");
                cmd->p_status = ft_export(cmd->data, cmd->data->vars, cmd->args);
        }
        else if (ft_strncmp(cmd->args[0], "unset", 5) == 0)
                cmd->p_status = ft_unset(cmd->data->vars, cmd->args);
        else if (ft_strncmp(cmd->args[0], "exit", 4) == 0)
                ft_exit(cmd->data, cmd->args);
        else if (ft_strncmp(cmd->args[0], "mhistory", 8) == 0)
        {
                show_history(cmd->data);
                cmd->p_status = 0;
        }
	cmd->data->last_status = cmd->p_status;
        return ;

}