#include "../data.h"
#include "../parser/parser.h"
#include "executor.h"
#include "../here_doc/here_doc.h"

int	redirect(t_cmd *cmd, int pipes, int *fds, int i)
{
        if (cmd->infile)
        {
                if (i != 0)
                        close(fds[(i - 1) * 2]);
                if (handle_infile(cmd, cmd->data) != 0)
                        return (1);
                dup2(cmd->fd_in, STDIN_FILENO);
                //close(cmd->fd_in);
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
                if (handle_outfile(cmd, cmd->data) != 0)
                        return (1);
                //handle_outfile(cmd->outfile, cmd->append, cmd->data); // y si error?
                dup2(cmd->fd_out, STDOUT_FILENO);
                //close(cmd->fd_out);
        }
        else if (i != pipes)
        {
                dup2(fds[(i * 2) + 1], STDOUT_FILENO);
                close(fds[(i * 2) + 1]);
        }
        return (0);
}
/*
int	redirect(t_cmd *cmd, int pipes, int *fds, int i)
{
        if (cmd->infile)
        {
                if (i != 0)
                        close(fds[(i - 1) * 2]);
                if (handle_infile(cmd, cmd->data) != 0)
                        return (1);
                dup2(cmd->fd_in, STDIN_FILENO);
                close(cmd->fd_in);
        }
        else if (cmd->fd_in != STDIN_FILENO && cmd->fd_in > 2)
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
                if (handle_outfile(cmd, cmd->data) != 0)
                        return (1);
                //handle_outfile(cmd->outfile, cmd->append, cmd->data); // y si error?
                dup2(cmd->fd_out, STDOUT_FILENO);
                close(cmd->fd_out);
        }
        else if (i != pipes)
        {
                dup2(fds[(i * 2) + 1], STDOUT_FILENO);
                close(fds[(i * 2) + 1]);
        }
        return (0);
}
*/
