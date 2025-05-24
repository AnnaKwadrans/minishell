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
                execute_line(data->cmds[i], data->pipes[i], data->fds);
		i++;
	}
	return ;
}

int	execute_line(t_cmd **cmds, int pipes, int *fds)
{
        int i;

        //printf("pipes: %d\n", pipes);
        if (pipes > 0)
                fds = create_pipes(pipes);
	i = 0;
        while (cmds[i])
        {
                cmds[i]->data->last_cmd = cmds[i];
                child(cmds[i], pipes, fds, i);
                i++;
        }
        close_fds(fds, pipes, -1, -1);
        if (fds)
                free(fds);
        while (wait(NULL) > 0)
                ;
        //parent(cmds, pipes, fds);
        return (0);
}

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
        {}
        else if (ft_strncmp(cmd->args[0], "cd", 2) == 0)
        {}
        else if (ft_strncmp(cmd->args[0], "env", 3) == 0)
        {}
        else if (ft_strncmp(cmd->args[0], "pwd", 3) == 0)
        {}
        else if (ft_strncmp(cmd->args[0], "export", 6) == 0)
        {}
        else if (ft_strncmp(cmd->args[0], "unset", 5) == 0)
        {}
        else if (ft_strncmp(cmd->args[0], "exit", 4) == 0)
        {}
        else if (ft_strncmp(cmd->args[0], "mhistory", 8) == 0)
        {
                show_history(cmd->data);
                cmd->p_status = 0;
        }
}

void    child(t_cmd *cmd, int pipes, int *fds, int i)
{
        //printf("check new %d", i);
        cmd->pid = fork();
        if (cmd->pid < 0)
                return (perror("Fork failed"));
        else if (cmd->pid == 0)
        {
                close_fds(fds, pipes, (i - 1) * 2, (i * 2) + 1);
                redirect(cmd, pipes, fds, i);
                if (is_builtin(cmd->args[0]))
                {       
                        exec_builtin(cmd);
                        exit(cmd->p_status);
                }
                else
                {
                        exec_cmd(cmd);
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



/*
int	execute_line(t_cmd **cmds, int pipes, int *fds)
{
	int	i;

	printf("pipes: %d\n", pipes);
        if (pipes == 0)
                single_child(cmds[0]);
        else
        {
                fds = create_pipes(pipes);
	        first_child(cmds[0], pipes, fds);
	        i = 1;
	        while (cmds[i] && i < pipes)
	        {
		        new_child(cmds[i], pipes, fds, i);
		        i++;
	        }
                if (i == pipes)
        		last_child(cmds[i], pipes, fds);
                close_fds(fds, pipes);
                free(fds);
        }
        parent(cmds, pipes);
        return (0);
}
*/

/*
void    last_child(t_cmd *cmd, int pipes, int *fds)
{
        // pipe i, fds[i]
        printf("check last 1");
        cmd->pid = fork();
        if (cmd->pid < 0)
        {
        // err
        }
        if (cmd->pid == 0)
        {       
                if (cmd->outfile)
                {
                        cmd->fd_out = handle_outfile(cmd->outfile, cmd->append);
                        dup2(cmd->fd_out, STDOUT_FILENO);
                        }
                        else
                        {
                                dup2(fds[(pipes - 1) * 2], STDIN_FILENO); //2
                                
                        }
                        //close_fds(fds, pipes);
                        exec_cmd(cmd);
                        printf("check last 2");
        }
        if (cmd->pid > 0)
        {
                //parent
        }
}

void    new_child(t_cmd *cmd, int pipes, int *fds, int i)
{
                // pipe i, fds[i]
                printf("check new 1");
                cmd->pid = fork();
                if (cmd->pid < 0)
                {
                        // err
                }
                if (cmd->pid == 0)
                {       
                        dup2(fds[(i - 1) * 2], STDIN_FILENO); //1: 0 
                        if (cmd->outfile)
                        {
                                cmd->fd_out = handle_outfile(cmd->outfile, cmd->append);
                                dup2(cmd->fd_out, STDOUT_FILENO);
                        }
                        else
                                dup2(fds[(i * 2) + 1], STDOUT_FILENO); //1: 3
                        
                        
                        // i = 1
                        //dup2(fds[0], STDIN_FILENO);
                        //dup2(fds[3], STDOUT_FILENO); // i * 2 + 1
                        // i = 2
                        //dup2(fds[2], STDIN_FILENO); // (i - 1) * 2
                        //dup2(fds[5], STDOUT_FILENO); // i * 2 + 1
                        // i = 3
                        //dup2(fds[4], STDIN_FILENO); // (i - 1) * 2
                        //dup2(fds[7], STDOUT_FILENO); // (i * 2) + 1
                        // i = 4 = pipes
                        //dup2(fds[6], STDIN_FILENO); // (i - 1) * 2
                        //close_fds(fds, pipes);
                        exec_cmd(cmd);
                        printf("check new 2");
                }
                if (cmd->pid > 0)
                {
                        //parent
                }
}

void    parent(t_cmd **cmds, int pipes, int *fds)
{
        int     i;
        
        //close_fds(fds, pipes, -1, -1);
        
        i = 0;
        
        while (i < pipes)
        {
                wait(NULL);
                //waitpid(cmds[i]->pid, NULL, WNOHANG);
                i++;
        }
        
       while (wait(NULL) > 0)
        ;
}
/*
void    first_child(t_cmd *cmd, int pipes, int *fds)
{
        // pipe 1, fds[0]
        printf("check first 1");
        cmd->pid = fork();
        if (cmd->pid < 0)
        {
                // err
        }
        if (cmd->pid == 0)
        {
                dup2(fds[1], STDOUT_FILENO); // (i * 2) + 1
                //close_fds(fds, pipes);
                exec_cmd(cmd);
                printf("check first 2");
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
                return (perror("fork failed"));
        else if (cmd->pid == 0)
        {
                if (cmd->infile)
                {
                        cmd->fd_in = handle_infile(cmd->infile, cmd->delimit);
                        dup2(cmd->fd_in, STDIN_FILENO);
                }
                if (cmd->outfile)
                {
                        cmd->fd_out = handle_outfile(cmd->outfile, cmd->append);
                        dup2(cmd->fd_out, STDOUT_FILENO);
                }
                exec_cmd(cmd);
        }
}
*/



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