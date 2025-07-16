/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varenv.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 00:17:48 by kegonza           #+#    #+#             */
/*   Updated: 2025/07/16 20:00:46 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARENV_H
# define VARENV_H

# include "../data.h"
# include "../libft/libft.h"

// AUX.C
char	*ft_strjoin_free(char *s1, char *s2);
int		ft_strcmp(const char *s1, const char *s2);
void	free_vars(t_vars *vars);
int		skip_var(const char *line, int i);
int		skip_quote(const char *line, int i);

// COUNTS.C
int		get_var_size(char *line, int start);
int		count_exportable_vars(t_data *data_program);
int		mtrx_size(char **mtrx);
int		count_vars(char *line);
int		size_total(char *line, char **values);
int		total_vars(t_data *data_program);

// CRUD.C
t_vars	**export_vars(t_data *data_program);
t_vars	*new_var(char *name, char *value, int is_exportable);
void	add_var(t_data *data_program, t_vars *new);
void	update_env(t_data *data_program);
size_t	cmd_array_size(t_cmd **cmd);

// SEARCH.C
t_vars	*search_var(t_data *data_program, char *name);
char	*get_var_value(t_data *data_program, char *name);
char	*fill_var_name(char *line, int start, int size);
char	*fill_var_values(t_data *data_program, char *line, int start);
char	**multi_search(t_data *data_program, char *line, int count);

// VARENV.C
void	show_vars(void *args);
void	init_env(t_data *data_program, char **env);
char	*expand_vars(t_data *data_program, char *line, bool rm_quotes, bool free_line);
void	update_shlvl(t_data *data);
void	example_new_vars(t_data *data_program);
char	*handle_single_quotes(char *result, char *line, int *i);
char	*handle_double_quotes(char *result, char *line, int *i,
			t_expand *exp);

#endif
