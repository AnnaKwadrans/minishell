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
# include "libft/libft.h"
# include "lexer.h"
# include "aux/aux.h"



// Estructura para almacenar los datos del programa

typedef struct s_data
{
	struct	s_lines	*line; // Lineas de entrada
	struct	s_cmd	**cmds; // Comandos para ejecutar
	struct	s_lines	*history_lines; // Historial de comandos ejecutados
	char			*tokens; // split por ;
	struct	s_vars	*vars; // Variables de entorno
	int				pipes; // Contador de pipes
	int				is_interactive; // Si es interactivo o no
}	t_data;

// Estructura para almacenar las variables de entorno "locales"
typedef struct s_vars
{
	char			*name; // Nombre de la variable
	char			*value; // Valor de la variable
	struct	s_vars	*next; // Siguiente variable
	int				is_exportable; // Si es exportable o no
} t_vars;

// Estructura para almacenar los comandos y ejecutarlos
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
	//struct	s_cmd *next; // esto creo que no lo necesitamos si no es una lista
	t_data	*data;
}	t_cmd;

// Estructura para almacenar las lineas de entrada (historial)
typedef struct s_lines
{
	char	*line; // Linea de entrada
	int		index; // Indice de la linea
	struct	s_lines	*next; // Siguiente linea
	t_data	*data; // Datos del programa
}	t_lines;

void	ft_printer_lines(t_lines *lines);
void	add_mhistory(t_data *data_program, char *input);
void	show_history(void *arg);

#endif
