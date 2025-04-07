#ifndef DATA_H
# define DATA_H
# include <termios.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>

typedef struct s_cmd
{
	char 	**args;
	char	**env;
	char 	*infile;
	int		fd_in;
	char 	*outfile;
	int		fd_out;
	int 	append;
	char	*delimit;
	pid_t 	pid;
	int		p_status;
	struct s_cmd *next;
}	t_cmd;

typedef struct s_lines
{
	char	*line;
	int		index;
	struct s_lines	*next;
}	t_lines;

typedef struct s_data
{
	t_lines	*line;
	t_cmd	*cmds;
	t_lines	*history_lines;
	int		pipes;
}	t_data;

void	ft_printer_lines(t_lines *lines);

#endif