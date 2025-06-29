#include "../data.h"
#include "../parser/parser.h"

// executor.c
int	execute_line(t_data *data);
int     *create_pipes(int pipes);
int     handle_cmd(t_data *data, t_cmd *cmd, int i);
void    close_fds(int *fds, int pipes, int wr, int rd);
int    child(t_cmd *cmd, int pipes, int *fds, int i);

// exec_builtin.c
bool    is_builtin(char *cmd);
int    exec_builtin(t_cmd *cmd, int pipes, int *fds, int i);
void    ft_builtin(t_cmd *cmd);

// redirect.c
int    redirect(t_cmd *cmd, int pipes, int *fds, int i);
int    redirect_input(t_cmd *cmd, int pipes, int *fds, int i);
int    redirect_output(t_cmd *cmd, int pipes, int *fds, int i);

// exec_cmd.c
void	exec_cmd(t_cmd *cmd);
char	**vars_to_char(t_vars *vars);
char	*get_str_var(char *name, char *value);
char	*get_paths(t_data *data_program);
char	*get_exec_path(t_cmd *cmd);
char	*get_path(char **cmd_tab, char **path_tab);

// infile.c
int	check_infile(char **infile, t_data *data);
int	open_infile(t_cmd *cmd, t_data *data);
int	handle_infile(t_cmd *cmd, t_data *data);

// outfile.c
int	check_outfile(char **outfile, t_data *data);
int	open_outfile(t_cmd *cmd, t_data *data);
int	handle_outfile(t_cmd *cmd, t_data *data);


// ft_cd
int     ft_env(t_vars *vars);
int    ft_pwd();
int     ft_unset(t_vars *vars, char **args);

int     ft_echo (t_data *data, char **args);
int	ft_export(t_data *data, t_vars *vars, char **args);
void     ft_exit(t_data *data, char **args);
int    ft_cd(t_data *data, char **args);
/*COMMIT CAMPUS 
int     ft_echo (t_data *data, char **args);
int     ft_export(t_data *data, char *name);
END COMMIT CAMPUS */