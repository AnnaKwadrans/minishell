#include "data.h"
#include "parser.h"

//void    exec_all_lines(t_data *data);
int	execute_line(t_data *data);
//void    single_child(t_cmd *cmd);
void	exec_cmd(t_cmd *cmd);
char	*get_path(char **cmd_tab, char **path_tab);
int     *create_pipes(int pipes);
void    close_fds(int *fds, int pipes, int wr, int rd);

bool    is_builtin(char *cmd);
void    exec_builtin(t_cmd *cmd, int pipes, int *fds, int i);
void    ft_builtin(t_cmd *cmd);


// executer.c
//int	check_infile(t_inf *infile, t_data *data);
int	check_infile(char **infile, t_data *data);
//int	open_infile(t_inf *infile, t_data *data);
int	open_infile(t_cmd *cmd, t_data *data);
//void	close_infds(t_inf *infile, int cont);
//int	handle_infile(t_inf *infile, t_data *data);
int	handle_infile(t_cmd *cmd, t_data *data);
//void	close_outfds(t_outf *outfile, int cont);
//int	check_outfile(t_outf *outfile, t_data *data);
int	check_outfile(char **outfile, t_data *data);
//int	open_outfile(t_outf *outfile, t_data *data);
int	open_outfile(t_cmd *cmd, t_data *data);
//int	handle_outfile(t_outf *outfile, t_data *data);
int	handle_outfile(t_cmd *cmd, t_data *data);

//int     execute_line(t_cmd ***cmds, int *pipes);
//int     execute_pipes(t_cmd *cmd, int pipes, int index);
//int	    exec_cmd(t_cmd *cmd);
//int     handle_infile(char *infile, t_data *data);
//int     handle_outfile(char *outfile, int append, t_data *data);
int	exec_line(t_cmd ***cmds, int *pipes);
//void    first_child(t_cmd *cmd, int pipes, int *fds);
//void    new_child(t_cmd *cmd, int pipes, int *fds, int i);
//void    last_child(t_cmd *cmd, int pipes, int *fds);
//void    parent(t_cmd **cmds, int pipes, int *fds);
//void	redirect_input(t_cmd *cmd, t_data *data, int i);
//void	redirect_output(t_cmd *cmd, t_data *data, int i);
//void	redirect(t_cmd *cmd, t_data *data, int i);
void    redirect(t_cmd *cmd, int pipes, int *fds, int i);

void    child(t_cmd *cmd, int pipes, int *fds, int i);
char	**vars_to_char(t_vars *vars);
char	*get_str_var(char *name, char *value);
char	*get_paths(t_data *data_program);

// ft_cd.c
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