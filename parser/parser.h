#ifndef PARSER_H
# define PARSER_H 

# include <stdlib.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include "../aux/aux.h"

typedef struct s_data t_data;
typedef struct s_lines t_lines;
typedef struct s_cmd t_cmd;

// data.c
void	init_data(t_data *data);
void	parse_data(char *input, t_data *data, char **envp);
t_lines	*get_line(t_data *data, char *input);
int	count_pipe(char *line); // ver si no tiene errores
void    handle_var(char *input, t_data *data);

//validator.c
bool	valid_input(char *input, t_data *data);
bool	even_quotes(char *line);
bool    valid_pipes(char *line); // ver si no tiene errores
int	empty_input(char *str);
bool    is_var(char *line);

// parser.c
t_cmd	**parse_line(char *input, int pipes, char **envp, t_data *data); // devuelve array de comandos
char	*vars_expansion(char *input, t_data *data, int *will_free);
int     is_expandable(char *input);
void	pipeline(t_data *data, t_cmd **cmd, char *cmd_aux);

// command.c
t_cmd	*get_cmd(char *aux); // se le pasa como parametro una parte del input que corresponde a un pipe
void	init_cmd(t_cmd *cmd); // inicializa la estructura

// args.c
char	**get_args(char *aux, int *index); // para obtener el array con el comando y argumentos
char	**append_args(char **args, char *aux, int *i); // para añadir los argumentos al array con el comando
int	count_no_quotes(char *arg);
char	*rm_quotes_arg(char *arg);
char	**rm_quotes(char **args);

// files.c
void	skip_delimit(char *aux, int *index);
void	get_infile(char *aux, int *index, char ***infile); // para obtener el infile (<) o delimitador (<<)
void	get_outfile(char *aux, int *index, char ***outfile, int *append);
char	**first_file(char *new_file);
char	**append_file(char **file, char *new_file);
char	*get_file_str(const char *aux, int *index); // funcion auxiliar para obtener el string outfile, infile o delimit

// pipe_split.c
int	close_quotes(char const *s); // devuelve el index donde terminan las comillas
char	**split_pipes(char const *s, char c); // un split pero tiene en cuenta comillas, devuelve un array de strings auxiliar para rellenar la estuctura t_cmd

// cleanup.c
void	clean_data_program(t_data *data); // libera la memoria de t_data después de ejecutar el comando excepto history_line
void	free_data(t_data *data); // libera todo de t_data pero está incompleta
void	free_cmd(t_cmd	*cmd);
void	free_line(t_lines *line);
void	free_data_vars(t_vars *vars);

// parser_utils.c
char	*get_var(char *line); // para obtener el valor de la variable de entorno
//estas tres probablemente para borrar
bool	is_set(char c, char const *set);
size_t	ft_strlen_set(const char *s, char *set);
char	*ft_strdup_set(const char *s, char *set);
void	print_cmd(t_cmd **cmds);

#endif
