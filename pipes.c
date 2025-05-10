#include "data.h"
#include "parser.h"
#include "executer.h"

int     *create_pipes(int pipes)
{
        int     *fds;
        int     i;

        if (pipes == 0)
                return (NULL);
        fds = malloc(sizeof(int) * pipes * 2);
        if (!fds)
                return (NULL);
        i = 0;
        while (i < pipes)
        {
                if (pipe(&fds[i * 2]) < 0)
                        return (NULL);
                i += 2;
        }
        return (fds);
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
/*
void    create_process(t_cmd *cmd, int pipes, int *fds)
{
        cmd->pid = fork;
        if (cmd->pid < 0)
        {
                //err
        }
        if (cmd->pid == 0)
        {
                child(cmd, );
        }


}
*/

void    exec_all_lines(t_data *data)
{
	int	i;

	i = 0;
	while (data->cmds[i])
	{
		execute_line(data->cmds[i], data->pipes[i], data->fds);
		i++;
	}
	return ;
}

int	execute_line(t_cmd **cmds, int pipes, int *fds)
{
	int	i;

	if (pipes == 0)
                single_child(cmds[0]);
        else
        {
                fds = create_pipes(pipes);
	        first_child(cmds[0], pipes, fds);
	        i = 1;
	        while (cmds[i] && i < pipes)
	        {
		        //new_child(cmds[i], pipes, fds);
		        i++;
	        }
	        if (i == pipes)
                {
		        //last_child(cmds[i], fds);
                }
                free(fds);
        }
        return (0);
}

void    parent(t_cmd **cmds, int pipes)
{
        int     i;
        
        i = 0;
        while (i <= pipes)
        {
                waitpid(cmds[i]->pid, NULL, 0);
                i++;
        }
}

void    first_child(t_cmd *cmd, int pipes, int *fds)
{
        // pipe 1, fds[0]
        cmd->pid = fork();
        if (cmd->pid < 0)
        {
                // err
        }
        if (cmd->pid == 0)
        {
                dup2(fds[1], STDOUT_FILENO);
                close_fds(fds, pipes, 1, -1);
                exec_cmd(cmd);
        }
        if (cmd->pid > 0)
        {
                //parent
        }
}

void    single_child(t_cmd *cmd)
{
        cmd->pid = fork();
        if (cmd->pid < 0)
        {
                // err
        }
        else if (cmd->pid == 0)
        {
                // in/out files
                exec_cmd(cmd);
        }
        else 
                waitpid(cmd->pid, NULL, 0);
}
/*
int     main(int argc, char **argv, char **envp)
{
        char    *line;
        t_data  *data;

        //line = ft_strdup("ls | sort -R | grep .c");
        line = ft_strdup("ls");
        init_data(data);
        parse_data(line, data, envp);
	execute_line(data->cmds[0], data->pipes[0], data->fds);
	clean_data_program(data);
        free(line);
        return (0);
}
*/
// cc pipes.c executer.c parser/*.c libft/libft.a aux/*.c history.c printer.c -lreadline -I/usr/local/opt/readline/include -L/usr/local/opt/readline/lib