#include <dirent.h>
#include <linux/limits.h>
#include <limits.h>
#include "../data.h"
#include "../libft/libft.h"
#include "../vars/varenv.h"
//#include "../aux/aux.h"
#include "../executor/executor.h"

static void	rm_first(t_vars **vars)
{
	t_vars	*temp;

	temp = *vars;
	*vars = (*vars)->next;
	free(temp->name);
	free(temp->value);
	temp->data = NULL;
	temp->next = NULL;
	// printf("CHILD\n");
	ft_env(*vars);
}

static void	rm_last(t_vars *vars)
{
	t_vars	*temp;

	temp = vars;
	while (vars && vars->next)
	{
		if (!vars->next->next)
		{
			free(vars->next->name);
			free(vars->next->value);
			vars->next->data = NULL;
			vars->next = NULL;
			// printf("CHILD\n");
			ft_env(temp);
			return ;
		}
		vars = vars->next;
	}
}

static void	rm_middle(t_vars *vars, char *name)
{
	t_vars	*temp;

	while (vars && vars->next && vars->next->next)
	{
		if (strncmp(vars->next->name, name, ft_strlen(name)) == 0)
		{
			temp = vars->next;
			vars->next = vars->next->next;
			free(temp->name);
			free(temp->value);
			temp->data = NULL;
			temp->next = NULL;
			// printf("CHILD\n");
			ft_env(vars);
			return ;
		}
		vars = vars->next;
	}
	// printf("CHILD\n");
	show_vars(vars);
}

int	ft_unset(t_vars *vars, char **args)
{
	int		i;
	t_vars	*start;

	if (!vars || !args)
		return (ft_putendl_fd("not enough arguments", 2), 0);
	start = vars;
	i = 1;
	while (args[i])
	{
		if (ft_strncmp(args[i], vars->name, ft_strlen(args[i])) == 0)
		{
			rm_first(&vars);
			break ;
		}
		while (vars && vars->next && vars->next->next)
		{
			if (ft_strncmp(args[i], vars->next->name, ft_strlen(args[i])) == 0)
			{
				rm_middle(start, args[i]);
				break ;
			}
			vars = vars->next;
		}
		if (ft_strncmp(args[i], vars->next->name, ft_strlen(args[i])) == 0)
		{
			rm_last(start);
			break ;
		}
		i++;
	}
	return (0);
}
