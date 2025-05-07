#include "../data.h"
#include "../aux/aux.h"
#include "../libft/libft.h"
#include "varenv.h"

void	free_vars(void *args)
{
	t_vars	*var;
	t_data	*data_program;

	data_program = (t_data *)args;
	var = data_program->vars;
	while (var)
	{
		free(var->name);
		free(var->value);
		free(var);
		var = var->next;
	}
}

void	show_vars(void *args)
{
	t_vars	*var;
	t_data	*data_program;
	int i;

	i = 1;
	data_program = (t_data *)args;
	var = data_program->vars;
	while (var)
	{
		printf("Variable %d:\n", i);
		printf("\tname: %s\n", var->name);
		printf("\tvalue: %s\n ", var->value);
		var = var->next;
		i++;
	}
}

t_vars	*new_var(char *name, char *value, int is_exportable)
{
	t_vars	*new;

	new = malloc(sizeof(t_vars));
	if (!new)
		return (NULL);
	new->name = ft_strdup(name);
	if (!new->name)
	{
		free(new);
		return (NULL);
	}
	new->value = ft_strdup(value);
	if (!new->value)
	{
		free(new->name);
		free(new);
		return (NULL);
	}
	new->is_exportable = is_exportable;
	new->next = NULL;
	printf("New variable created: %s = %s\n", new->name, new->value);
	return (new);
}

void	add_var(t_data *data_program, t_vars *new)
{
	t_vars	*tmp;

	printf("Adding variable: %s = %s\n", new->name, new->value);
	if (!data_program->vars)
	{
		data_program->vars = new;
		return ;
	}
	tmp = data_program->vars;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}


int ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

t_vars	*search_var(t_data *data_program, char *name)
{
	t_vars	*tmp;

	tmp = data_program->vars;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}


void init_env(t_data *data_program, char **env)
{
	int 	i;
	char	**split;
	t_vars	*vars;
	t_vars	*new;

	vars = data_program->vars;
	i = 0;
	while (env[i])
	{
		split = ft_split(env[i], '='); // Divide la variable en nombre y valor
		// printf("Variable de entorno: %s = %s\n", split[0], split[1]);
		new = malloc(sizeof(t_vars));
		new->name = ft_strdup(split[0]); // Asigna el nombre de la variable
		if (split[1])
			new->value = ft_strdup(split[1]); // Asigna el valor de la variable
		new->is_exportable = 1; // viene del entorno, así que está exportada
		add_var(data_program, new); // Si ya hay variables, añade la nueva al final
		free(split[0]);
		free(split[1]);
		free(split);
		i++;
	}
}

int	count_exportable_vars(t_data *data_program)
{
	t_vars	*tmp;
	int		count;

	tmp = data_program->vars;
	count = 0;
	while (tmp)
	{
		if (tmp->is_exportable)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

t_vars	**export_vars(t_data *data_program)
{
	t_vars	*tmp;
	t_vars	**exported_vars;
	int		i;

	tmp = data_program->vars;
	i = 0;
	exported_vars = malloc(sizeof(t_vars *) * (count_exportable_vars(data_program) + 1));
	if (!exported_vars)
		return (NULL);
	while (tmp)
	{
		if (tmp->is_exportable)
		{
			exported_vars[i] = tmp;
			i++;
		}
		tmp = tmp->next;
	}
	exported_vars[i] = NULL; // Termina la lista con NULL
	return (exported_vars);
}



void example_new_vars(t_data *data_program)
{
	t_vars	*new_var1;
	t_vars	*new_var2;
	t_vars	*new_var3;
	t_vars	*new_var4;
	t_vars	*new_var5;

	new_var1 = new_var("MY_VAR", "Hello World", 1);
	new_var2 = new_var("MY_VAR2", "42", 0);
	new_var3 = new_var("MY_VAR3", "Hello", 1);
	new_var4 = new_var("MY_VAR4", "World", 0);
	new_var5 = new_var("MY_VAR5", "!", 1);
	add_var(data_program, new_var1);
	add_var(data_program, new_var2);
	add_var(data_program, new_var3);
	add_var(data_program, new_var4);
	add_var(data_program, new_var5);
}

// int main(int argc, char **argv, char **env)
// {
// 	t_data	*data_program;
// 	t_vars	*var;
// 	t_vars	**exported_vars;

// 	data_program = malloc(sizeof(t_data));
// 	if (!data_program)
// 		return (1);
// 	data_program->vars = NULL;
// 	init_env(data_program, env);
// 	example_new_vars(data_program);
// 	show_vars(data_program);
// 	printf("\n<<------------------ exportable vars ------------------>>\n\n");
// 	exported_vars = export_vars(data_program);
// 	if (!exported_vars)
// 	{
// 		printf("Error al exportar las variables\n");
// 		return (1);
// 	}
// 	for (int i = 0; exported_vars[i]; i++)
// 	{
// 		printf("Variable exportable %d:\n", i + 1);
// 		printf("\tname: %s\n", exported_vars[i]->name);
// 		printf("\tvalue: %s\n ", exported_vars[i]->value);
// 	}
// 	// var = search_var(data_program, "PWD");
// 	// if (var)
// 	// 	printf("Variable encontrada: %s=%s\n", var->name, var->value);
// 	// else
// 	// 	printf("Variable no encontrada\n");
// 	free_vars(data_program);
// 	free(data_program);
// 	return (0);
// }

// PARA PROBAR ESTAS FUNCIONES CON LIBFT
// cc libft/libft.a vars/*.c
