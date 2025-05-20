#include "../data.h"

// CRUD.C
void 	add_var(t_data *data_program, t_vars *new);
t_vars 	*new_var(char *name, char *value, int is_exportable);

// SEARCH.C
t_vars	*search_var(t_data *data_program, char *name);
char *get_var_value(t_data *data_program, char *name);
char *fill_var_name(char *line, int start, int size);
char *fill_var_values(t_data *data_program, char *line, int start);
char **multi_search(t_data *data_program, char *line, int count);

// VARENV.C
char *expand_vars(t_data *data_program, char *line);
t_vars **export_vars(t_data *data_program);
void 	show_vars(void *args);
void init_env(t_data *data_program, char **env);

// COUNTS.C
int get_var_size(char *line, int start);
int count_exportable_vars(t_data *data_program);
int count_vars(char *line);
int size_total(char *line, char **values);

// AUX.C
char *ft_strjoin_free(char *s1, char *s2);
int ft_strcmp(const char *s1, const char *s2);
void free_vars(void *args);
int mtrx_size(char **mtrx);
