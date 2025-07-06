#ifndef BUILTINS_H
# define BUILTINS_H
# ifdef LINUX_OS
#  include <linux/limits.h>
# else
#  include <limits.h>
#include <dirent.h>
# endif
# include "../vars/varenv.h"
# include "../parser/parser.h"
# include "../data.h"
# include "../libft/libft.h"
# include "../executor/executor.h"

int	ft_echo (t_data *data, char **args);
int	ft_pwd(void);
int	ft_env(t_vars *vars);
int	ft_cd(t_data *data, char **args);
void	ft_exit(t_data *data, char **args);
int	ft_export(t_data *data, t_vars *vars, char **args);
int	ft_unset(char **args, t_data *data);

#endif
