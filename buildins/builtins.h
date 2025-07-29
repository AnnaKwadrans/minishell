/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 18:01:34 by akwadran          #+#    #+#             */
/*   Updated: 2025/07/14 21:59:45 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# ifdef __linux__
#  include <linux/limits.h>
# else
#  include <limits.h>
# endif
# include <dirent.h>
# include "../vars/varenv.h"
# include "../parser/parser.h"
# include "../data.h"
# include "../libft/libft.h"
# include "../executor/executor.h"

int	ft_echo(t_data *data, char **args);
int	ft_pwd(void);
int	ft_env(t_vars *vars);
int	ft_cd(t_data *data, char **args);
int	ft_exit(t_data *data, char **args);
int	ft_export(t_data *data, t_vars *vars, char **args);
int	sort_and_print(t_data *data, t_vars *vars, char **args);
void	update_value(t_vars *found, t_vars *exported);
int	ft_unset(char **args, t_data *data);

#endif
