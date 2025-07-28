/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:44:26 by akwadran          #+#    #+#             */
/*   Updated: 2025/07/28 19:37:22 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>

# include "../data.h"
# include "../parser/parser.h"
# include "../here_doc/here_doc.h"
# include "../buildins/builtins.h"
# include "../vars/varenv.h"

// executor.c
int		execute_line(t_data *data);
int		*create_pipes(int pipes);
void	handle_cmd(t_data *data, t_cmd *cmd, int i);
void	close_fds(int *fds, int pipes, int wr, int rd);
int		child(t_cmd *cmd, int pipes, int *fds, int i);

// exec_builtin.c
bool	is_builtin(char *cmd);
int		exec_builtin(t_cmd *cmd, int pipes, int *fds, int i);
int		ft_builtin(t_cmd *cmd);
int		save_stdfds(t_cmd *cmd, int *saved_stdin, int *saved_stdout);
void	restore_stdfds(t_cmd *cmd, int *saved_stdin, int *saved_stdout);

// redirect.c
int		redirect(t_cmd *cmd, int pipes, int *fds, int i);
int		redirect_input(t_cmd *cmd, int pipes, int *fds, int i);
int		redirect_output(t_cmd *cmd, int pipes, int *fds, int i);
void	redir_err_handler(int *fds, int i, int pipes);

// exec_cmd.c
void	exec_cmd(t_cmd *cmd);
char	**vars_to_char(t_vars *vars);
char	*get_str_var(char *name, char *value);
char	*get_paths(t_data *data_program);
char	*get_exec_path(t_cmd *cmd);
char	*get_path(char **cmd_tab, char **path_tab);

// infile.c
int		check_infile(char **infile, t_data *data);
int		open_infile(t_cmd *cmd, t_data *data);
int		handle_infile(t_cmd *cmd, t_data *data);

// outfile.c
int		check_outfile(char **outfile, t_data *data);
int		open_outfile(t_cmd *cmd, t_data *data);
int		handle_outfile(t_cmd *cmd, t_data *data);

#endif