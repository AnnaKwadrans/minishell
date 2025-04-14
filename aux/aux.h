#ifndef AUX_H
# define AUX_H

// 👇 Forward declaration
typedef struct s_cmd t_cmd;
typedef struct s_data t_data;
typedef struct s_lines t_lines;

// LINES_FUNCTIONS

t_lines *last_line_history(t_lines *cmd);
t_lines *new_line(char *line, t_data *data_program);
void 	*new_line_history(t_lines *line, void *args);

// ARRAY FUNCTIONS

size_t	array_size(char **array);
void	print_array(char **array);
void	free_array(char **array);
char	**join_arrays(char **array, char **add);

#endif
