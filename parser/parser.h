#ifndef PARSER_H
# define PARSER_H 

# include <stdlib.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include "../aux/aux.h"

typedef struct s_data t_data;
typedef struct s_lines t_lines;
typedef struct s_cmd t_cmd;

// parser.c
t_cmd	**parse_line(char *input, int pipes, char **envp, t_data *data); // devuelve array de comandos
t_cmd	*get_cmd(char *aux); // se le pasa como parametro una parte del input que corresponde a un pipe
void	init_cmd(t_cmd *cmd); // inicializa la estructura
void	get_infile(char *aux, int *index, char ***infile); // para obtener el infile (<) o delimitador (<<)
//void	get_infile(char *aux, int *index, t_inf **infile);
//void	add_infile(t_inf *infile, t_inf *new);
void	get_outfile(char *aux, int *index, char ***outfile, int *append);
char	**first_file(char *new_file);
char	**append_file(char **file, char *new_file);
//void	get_outfile(char *aux, int *index, t_outf **outfile); // para obtener el outfile (>) y el bool append (>>)
//void	add_outfile(t_outf *outfile, t_outf *new);
//void	print_outfiles(t_outf *outfile);
//void	print_infiles(t_inf *infile);
char	*get_file_str(const char *aux, int *index); // funcion auxiliar para obtener el string outfile, infile o delimit
char	**get_args(char *aux, int *index); // para obtener el array con el comando y argumentos
char	**append_args(char **args, char *aux, int *i); // para añadir los argumentos al array con el comando
int     *get_pipes(char **part_lines, size_t size);
char	**first_file(char *new_file);
char	**append_file(char **file, char *new_file);
int	check_infile(char **infile, t_data *data);
int	open_infile(t_cmd *cmd, t_data *data);
void	print_cmd(t_cmd **cmds);

// pipe_split.c
int	close_quotes(char const *s); // devuelve el index donde terminan las comillas
char	**split_pipes(char const *s, char c); // un split pero tiene en cuenta comillas, devuelve un array de strings auxiliar para rellenar la estuctura t_cmd

// cleanup.c
void	clean_data_program(t_data *data); // libera la memoria de t_data después de ejecutar el comando excepto history_line
void	free_data(t_data *data); // libera todo de t_data pero está incompleta
void	free_cmd(t_cmd	*cmd);
void	free_line(t_lines *line);
void	free_data_vars(t_vars *vars);

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
int		is_valid(char *str);

//char	*trim_quotes(char *input);
int	count_no_quotes(char *arg);
char	*rm_quotes_arg(char *arg);
char	**rm_quotes(char **args);

#endif
