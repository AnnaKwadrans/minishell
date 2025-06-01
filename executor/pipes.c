#include "../data.h"
#include "../parser.h"
#include "../executor.h"
#include "../here_doc/here_doc.h"

void    exec_all_lines(t_data *data)
{
	int	i;

	i = 0;
	while (data->cmds[i])
	{
                execute_line(data->cmds[i], data->pipes[i], data->fds, &data->last_status);
                printf("LAST LAST STATUS: %d\n", data->last_status);
		i++;
	}
	return ;
}

int	execute_line(t_cmd **cmds, int pipes, int *fds, int *last_status)
{
        int i;
        int status;

        //printf("pipes: %d\n", pipes);
        if (pipes > 0)
                fds = create_pipes(pipes);
	i = 0;
        while (cmds[i])
        {
                if (is_builtin(cmds[i]->args[0]))
                {       
                        exec_builtin(cmds[i]);
                        exit(cmds[i]->p_status);
                }
                else
                        child(cmds[i], pipes, fds, i);
                i++;
        }
        close_fds(fds, pipes, -1, -1);
        if (fds)
                free(fds);
        i = 0;
        while (waitpid(-1, &status, 0) > 0)
        {
                        *last_status = WEXITSTATUS(status);
                        //printf("CHILD %d\n", *last_status);
        }
        //printf("LAST STATUS %d\n", *last_status);
        return (0);
}

int     *create_pipes(int pipes)
{
        int     *fds;
        int     i;

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
        /*
        i = 0;
        while (i < pipes)
        {
                printf("i %d: %d %d\n", i, fds[i * 2], fds[(i * 2) + 1]);
                i++;
        }*/
        return (fds);
}

bool    is_builtin(char *cmd)
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

void    exec_builtin(t_cmd *cmd)
{
        if (ft_strncmp(cmd->args[0], "echo", 4) == 0)
                cmd->p_status = ft_echo(cmd->data, cmd->args);
        else if (ft_strncmp(cmd->args[0], "cd", 2) == 0)
        {}
        else if (ft_strncmp(cmd->args[0], "env", 3) == 0)
                cmd->p_status = ft_env(cmd->data->vars);
        else if (ft_strncmp(cmd->args[0], "pwd", 3) == 0)
                cmd->p_status = ft_pwd();
        else if (ft_strncmp(cmd->args[0], "export", 6) == 0)
                cmd->p_status = ft_export(cmd->data, cmd->args[1]);
        else if (ft_strncmp(cmd->args[0], "unset", 5) == 0)
                cmd->p_status = ft_unset(cmd->data->vars, cmd->args);
        else if (ft_strncmp(cmd->args[0], "exit", 4) == 0)
        {}
        else if (ft_strncmp(cmd->args[0], "mhistory", 8) == 0)
        {
                show_history(cmd->data);
                cmd->p_status = 0;
        }
        return ;
}

void    child(t_cmd *cmd, int pipes, int *fds, int i)
{
        //printf("check new %d", i);
        cmd->pid = fork();
        printf("check pid: %d\n", cmd->pid);
        if (cmd->pid < 0)
                return (perror("Fork failed"));
        else if (cmd->pid == 0)
        {
                close_fds(fds, pipes, (i - 1) * 2, (i * 2) + 1);
                redirect(cmd, pipes, fds, i);
                //cmd->data->last_cmd = &cmd;
                if (is_builtin(cmd->args[0]))
                {       
                        exec_builtin(cmd);
                        exit(cmd->p_status);
                }
                else
                {
                        exec_cmd(cmd);
                        exit(cmd->p_status);
                }
        }
        else if (cmd->pid > 0)
                return ;
}

void    close_fds(int *fds, int pipes, int wr, int rd)
{
        int     i;

        i = 0;
        while (i < (pipes * 2))
        {
                if (i != wr && i != rd)
                        close(fds[i]);
                i++;
        }
}

void    redirect(t_cmd *cmd, int pipes, int *fds, int i)
{
        if (cmd->infile)
        {
                if (i != 0)
                        close(fds[(i - 1) * 2]);
                cmd->fd_in = handle_infile(cmd->infile, cmd->delimit);
                dup2(cmd->fd_in, STDIN_FILENO);
                close(cmd->fd_in);
        }
        else if (cmd->fd_in != STDIN_FILENO)
        {
                if (i != 0)
                        close(fds[(i - 1) * 2]);
                dup2(cmd->fd_in, STDIN_FILENO);
                close(cmd->fd_in);
        }
        else if (i != 0)
        {
                dup2(fds[(i - 1) * 2], STDIN_FILENO); // 0:-2 1:0, 2:2, 3:4 
                                                        //0: 
                close(fds[(i - 1) * 2]);
        }
        if (cmd->outfile)
        {
                if (i != pipes)
                        close(fds[(i * 2) + 1]); // 0:1 1:3 2:5 3:7
                cmd->fd_out = handle_outfile(cmd->outfile, cmd->append);
                dup2(cmd->fd_out, STDOUT_FILENO);
                close(cmd->fd_out);
        }
        else if (i != pipes)
        {
                dup2(fds[(i * 2) + 1], STDOUT_FILENO);
                close(fds[(i * 2) + 1]);
        }
}
