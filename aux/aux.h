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



#endif
