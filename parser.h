#ifndef PARSER_H
# define PARSER_H 

# include <stdlib.h>
# include <stdbool.h>
# include "libft/libft.h"
# include "aux/aux.h"

typedef struct s_data t_data;
typedef struct s_lines t_lines;
typedef struct s_cmd t_cmd;

// parser.c
t_cmd	**parse_line(char *input, int pipes, char **envp, t_data *data); // devuelve array de comandos
t_cmd	*get_cmd(char *aux); // se le pasa como parametro una parte del input que corresponde a un pipe
t_cmd	*init_cmd(); // inicializa la estructura
char	*get_infile(char *aux, char **delimit, int *index); // para obtener el infile (<) o delimitador (<<)
char	*get_outfile(char *aux, int *append, int *index); // para obtener el outfile (>) y el bool append (>>)
char	*get_file_str(const char *aux, int *index); // funcion auxiliar para obtener el string outfile, infile o delimit
char	**get_args(char *aux, int *index); // para obtener el array con el comando y argumentos
char	**append_args(char **args, char *aux, int *i); // para añadir los argumentos al array con el comando
int     *get_pipes(char **part_lines, size_t size);

// pipe_split.c
int	close_quotes(char const *s); // devuelve el index donde terminan las comillas
char	**split_pipes(char const *s, char c); // un split pero tiene en cuenta comillas, devuelve un array de strings auxiliar para rellenar la estuctura t_cmd

// cleanup.c
void	clean_data_program(t_data *data); // libera la memoria de t_data después de ejecutar el comando excepto history_line
void	free_data(t_data *data); // libera todo de t_data pero está incompleta
void	free_cmd(t_cmd	*cmd);
void	free_line(t_lines *line);

//data.c - esto lo tenemos duplicado, probablemente para borrar
void	init_data(t_data *data);
void	parse_data(char *input, t_data *data, char **envp);
int	count_pipe(char *line);
bool	even_quotes(char *line);
t_lines	*get_line(t_data *data, char *input);

// lexer_utils.c
char	*get_var(char *line); // para obtener el valor de la variable de entorno
//estas tres probablemente para borrar
bool	is_set(char c, char const *set);
size_t	ft_strlen_set(const char *s, char *set);
char	*ft_strdup_set(const char *s, char *set);

//validator.c
bool    valid_pipes(char *line);
bool    is_var(char *line);
void    handle_var(char *input, t_data *data);


#endif
