#include "executor.h"

bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "echo", 4) == 0 || ft_strncmp(cmd, "cd", 2) == 0
		|| ft_strncmp(cmd, "env", 3) == 0 || ft_strncmp(cmd, "pwd", 3) == 0
		|| ft_strncmp(cmd, "export", 6) == 0 || ft_strncmp(cmd, "unset", 5) == 0
		|| ft_strncmp(cmd, "exit", 4) == 0)
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
        int     saved_stdin;
        int     saved_stdout;

        if (cmd->data->pipes == 0)
        {
                saved_stdin = dup(STDIN_FILENO);
                saved_stdout = dup(STDOUT_FILENO);
                //printf("check pid: %d\n", cmd->pid);
                close_fds(fds, pipes, (i - 1) * 2, (i * 2) + 1);
	        //redirect(cmd, cmd->data, i);
	        if (redirect(cmd, pipes, fds, i) != 0)
		return (1);
                ft_builtin(cmd);
                dup2(saved_stdin, STDIN_FILENO);
                close(saved_stdin);
                dup2(saved_stdout, STDOUT_FILENO);
                close(saved_stdout);
        }
        else
        {
                child(cmd, pipes, fds, i);
                /*cmd->pid = fork();
                //printf("check pid: %d\n", cmd->pid);
                if (cmd->pid < 0)
                        return (perror("Fork failed"), 2);
                else if (cmd->pid == 0)
                {
                        close_fds(fds, pipes, (i - 1) * 2, (i * 2) + 1);
                        if (redirect(cmd, pipes, fds, i) != 0)
                                return (1);
                        //cmd->data->last_cmd = &cmd;
        
                        ft_builtin(cmd);
                        exit(cmd->p_status);

                }
                else if (cmd->pid > 0)
                        return (0);*/
        }
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
