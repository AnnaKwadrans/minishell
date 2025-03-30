#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>

typedef struct s_cdm
{
	char 	**args;
	char	**env;
	char 	*infile;
	int		fd_in;
	char 	*outfile;
	int		fd_out;
	int 	append;
	pid_t 	pid;
	int		p_status;
	struct s_cdm *next;
}	t_cdm;

typedef struct s_data
{
	t_lines	*top;
	t_lines	*next;
	int		size;
}	t_lines;

typedef struct s_cmd
{
	int	in_fd;
	int	out_fd;
	char	*cmd;
	char	**cmd_args;
	int	status;
}	t_cmd;
