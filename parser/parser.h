/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:54:53 by akwadran          #+#    #+#             */
/*   Updated: 2025/07/12 16:00:50 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H 

# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "../aux/aux.h"
# include "../data.h"
# include "../vars/varenv.h"
# include "../here_doc/here_doc.h"
# include "../executor/executor.h"

typedef struct s_data	t_data;
typedef struct s_cmd	t_cmd;

// data.c
void	init_data(t_data *data);
void	parse_data(char *input, t_data *data, char **envp);
int		count_pipe(char *line); // ver si no tiene errores
void	handle_var(char *input, t_data *data);

//validator.c
bool	valid_input(char *input, t_data *data);
bool	even_quotes(char *line);
bool	valid_pipes(char *line); // ver si no tiene errores
int		empty_input(char *str);
bool	is_var(char *line);

// parser.c
t_cmd	**parse_line(char *input, int pipes, char **envp, t_data *data);
void	vars_expansion(t_data *data, t_cmd *cmd);
int		is_expandable(char *input);
void	pipeline(t_data *data, char **cmd_aux, int i);
void	init_cmd(t_cmd *cmd); // inicializa la estructura

// command.c
t_cmd	*get_cmd(char *aux);
t_cmd	*fill_out_cmd(t_cmd *cmd, char *aux);
void	get_infile(char *aux, int *index, char ***infile);
void	get_outfile(char *aux, int *index, char ***outfile, int *append);
char	**get_args(char *aux, int *index);

// command_utils.c
void	skip_delimit(char *aux, int *index);
char	**first_file(char *new_file);
char	**append_file(char **file, char *new_file);
char	*get_file_str(const char *aux, int *index);
char	**append_args(char **args, char *aux, int *i);

// quotes.c
int		count_no_quotes(char *arg);
char	*rm_quotes_arg(char *arg);
//char	**rm_quotes(char **args);
bool	cpy_char(char arg, bool *q_simple, bool *q_double);

// pipe_split.c
int		close_quotes(char const *s);
char	**split_pipes(char const *s, char c);

// cleanup.c
void	clean_data_program(t_data *data);
void	free_data(t_data *data); // libera todo de t_data pero está incompleta
void	free_cmds(t_data *data);
void	free_cmd(t_cmd	*cmd);
void	free_data_vars(t_vars *vars);

// parser_utils.c
char	*get_var(char *line); // para obtener el valor de la variable de entorno
bool	is_set(char c, char const *set);
size_t	ft_strlen_set(const char *s, char *set);
char	*ft_strdup_set(const char *s, char *set);
void	print_cmd(t_cmd **cmds);

void	rm_quotes(t_data *data, t_cmd *cmd);
bool	has_quotes_to_rm(char *str);

#endif
