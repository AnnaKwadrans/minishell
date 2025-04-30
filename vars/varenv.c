#include "../data.h"
#include "../aux/aux.h"
#include "../libft/libft.h"
#include "../lexer.h"

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

	i = 0;
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
	return (new);
}

void	add_var(t_data *data_program, t_vars *new)
{
	t_vars	*tmp;

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

int main(int argc, char **argv, char **env)
{
	t_data	*data_program;
	t_vars	*var;

	data_program = malloc(sizeof(t_data));
	if (!data_program)
		return (1);
	data_program->vars = NULL;
	init_env(data_program, env);
	// show_vars(data_program);
	var = search_var(data_program, "PWD");
	if (var)
		printf("Variable encontrada: %s=%s\n", var->name, var->value);
	else
		printf("Variable no encontrada\n");
	free_vars(data_program);
	free(data_program);
	return (0);
}

// PARA PROBAR ESTAS FUNCIONES CON LIBFT
// cc libft/libft.a vars/*.c
