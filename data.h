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
	struct t_cmd	**cmd;
	int		*pipes;
	int		total_pipes;
} t_data;
