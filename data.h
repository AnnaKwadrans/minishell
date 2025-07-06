#ifndef DATA_H
# define DATA_H

# include <termios.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <stdbool.h>

# include "libft/libft.h"
# include "signals/signals.h"
# include "aux/aux.h"

extern int g_sigint_received;

typedef struct s_heredoc	t_heredoc;
typedef struct s_data		t_data;
typedef struct s_vars		t_vars;
typedef struct s_cmd		t_cmd;

// Estructura para expandir variables
typedef struct s_expand
{
	t_data	*data; // Datos del programa
	char	**values; // Valores de las variables
	int		count; // Contador de variables
}	t_expand;

// Estructura para here_doc
typedef struct s_heredoc
{
	char	*delimiter; // Delimitador
	int		is_expandable; // Si es expandible o no
	char	**buffer; // Buffer para almacenar las lineas
}	t_heredoc;

// Estructura para almacenar los datos del programa
typedef struct s_data
{
	//struct s_lines	*line; // Lineas de entrada
	struct s_cmd	**cmds; // Comandos para ejecutar
	struct s_vars	*vars; // Variables de entorno
	int				pipes; // Contador de pipes
	int				is_interactive; // Si es interactivo o no
	int				is_expandable; // Si es expandible o no
	int				*fds;
	int				last_status;
}	t_data;

// Estructura para almacenar las variables de entorno "locales"
typedef struct s_vars
{
	char			*name; // Nombre de la variable
	char			*value; // Valor de la variable
	struct s_vars	*next; // Siguiente variable
	int				is_exportable; // Si es exportable o no
	t_data			*data;
}	t_vars;

// Estructura para almacenar los comandos y ejecutarlos
typedef struct s_cmd
{
	char		**args;
	char		**infile;
	int			fd_in;
	char		**outfile;
	int			fd_out;
	int			append;
	t_heredoc	*heredoc;
	pid_t		pid;
	int			p_status;
	t_data		*data;
	bool		is_builtin;
}	t_cmd;

void	add_mhistory(t_data *data_program, char *input);
void	show_history(void *arg);
void	free_cmd(t_cmd *cmd);

#endif
