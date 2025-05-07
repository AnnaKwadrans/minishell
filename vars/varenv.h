#include "../data.h"

void 	free_vars(void *args);
void 	show_vars(void *args);
void 	add_var(t_data *data_program, t_vars *new);
t_vars 	*new_var(char *name, char *value, int is_exportable);
t_vars	*search_var(t_data *data_program, char *name);
void init_env(t_data *data_program, char **env);
int count_exportable_vars(t_data *data_program);
t_vars **export_vars(t_data *data_program);
void example_new_vars(t_data *data_program);
