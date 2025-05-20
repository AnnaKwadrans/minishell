#include "varenv.h"

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
