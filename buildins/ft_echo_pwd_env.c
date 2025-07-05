#ifdef __linux__
# include <linux/limits.h>
#else
# include <limits.h>
#endif
#include <dirent.h>
#include "../data.h"
#include "../libft/libft.h"
#include "../vars/varenv.h"
//#include "../aux/aux.h"
#include "../executor/executor.h"

static int	is_correct_flag(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] != '-')
		return (0);
	i++;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo (t_data *data, char **args)
{
	int	i;
	int	size;
	int	is_n_flag;

	if (!args[1])
	{
		printf("\n");
		return (0);
	}
	/*if (ft_strncmp(args[1], "?", 1) == 0)
	{
		printf("STATUS %d\n", data->last_status);
		return (0);
	}*/
	size = array_size(args) - 1;
	if (args[1])
		is_n_flag = is_correct_flag(args[1]);
	i = 1;
	if (is_n_flag)
		i = 2;
	while (i < size)
	{
		printf("%s ", args[i]);
		i++;
	}
	printf("%s", args[i]);
	if (!is_n_flag)
		printf("\n");
	return (0);
}


int	ft_pwd(void)
{
	char	path[PATH_MAX];

	if (getcwd(path, PATH_MAX) == NULL)
	{
		perror("getcwd failed");
		return (1);
	}
	printf("%s\n", path);
	return (0);
}

static void	pre_env(t_data *data_program)
{
	t_vars	*var;

	if (!data_program || !data_program->vars)
		return ;
	var = search_var(data_program, "_");
	if (var)
	{
		free(var->value);
		var->value = ft_strdup("/usr/bin/env");
	}
	else
	{
		var = new_var("_", "/usr/bin/env", 1);
		var->data = data_program;
		add_var(data_program, var);
	}
}

int	ft_env(t_vars *vars)
{
	if (!vars)
		return (ft_putendl_fd("no vars", 2) , -1);
	pre_env(vars->data);
	while (vars)
	{
		if (vars->is_exportable)
			printf("%s=%s\n", vars->name, vars->value);
		vars = vars->next;
	}
	return (0);
}



/*
int main(int argc, char **argv, char **envp)
{
        char    *path = malloc(50);
        char    *path3;
        
        ft_pwd();
        //scanf("%s", path);
        //if (chdir(path) == -1)
        //        printf("fail");
        //else
        //        printf("success\n");
        /*path3 = getcwd(path2, 1024);
        if (path3 == NULL)
                printf("fail\n");
        else
                printf("3: %s\n", path3);
        printf("end :%s", path2);
        free(path);*/
        //free(path2);
        /*
        return (0);
}
*/
