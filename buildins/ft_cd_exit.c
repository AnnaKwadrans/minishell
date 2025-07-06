#ifdef LINUX_OS
# include <linux/limits.h>
#else
# include <limits.h>
#endif
#include "builtins.h"
#include "../vars/varenv.h"
#include "../parser/parser.h"

static void	update_pwd_var(t_data *data)
{
	t_vars	*pwd;
	char	path[PATH_MAX];

	if (getcwd(path, PATH_MAX) == NULL)
		return (perror("getcwd failed"));
	pwd = search_var(data, "PWD");
	free(pwd->value);
	pwd->value = ft_strdup(path);
	return ;
}

int	ft_cd(t_data *data, char **args)
{
	t_vars	*home_var;
	char	*home_path;

	if (array_size(args) > 2)
	{ 
		ft_putendl_fd("too many arguments", 2);
		return (1);
	 }
	else if (array_size(args) == 1 || ft_strncmp(args[1], "~", 1) == 0)
	{
		home_var = search_var(data, "HOME");
		if (chdir(home_var->value) == -1)
			return (perror("chdir failed"), 1);
	}
	else 
	{
		if (chdir(args[1]) == -1)
		return (perror("chdir failed"), 1);
	}
	update_pwd_var(data);
	return (0);
}

void	ft_exit(t_data *data, char **args)
{
	int	status;

	status = data->last_status;
	free_data(data);
	exit(status);
}
