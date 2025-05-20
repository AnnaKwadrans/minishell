#include "varenv.h"

int	get_var_size(char *line, int start)
{
	int size;
	int i;	

	size = 0;
	i = start;
	while (line[i])
	{
		if (line[i] == '_' || ft_isalnum(line[i]))
			size++;
		else
			break ;
		i++;
	}
	return (size);
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

int	count_vars(char *line)
{
	int count = 0;
	int i = 0;

	while (line[i] != '\0')
	{
		if (line[i] == '$' && (line[i + 1] != '\0' || line [i + 1] != '$'))
		{
			count++;
			i++;
			while (line[i] && (line[i] == '_' || ft_isalnum(line[i])))
				i++;
		}
		else if (line[i] == '\"' || line[i] == '\'')
		{
			i++;
			while (line[i] && line[i] != line[i - 1])
				i++;
		}
		else if (line[i] == '\\')
			i += 2;
		else
			i++;
	}
	return (count);
}

int size_total(char *line, char **values)
{
	int result;
	int i;
	int j;
	
	j = 0;
	result = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '$')
		{
			result += ft_strlen(values[j++]);
			while (line[i] && (line[i] == '$' || line[i] == '_' || ft_isalnum(line[i])))
				i++;
		}
		else if (line[i] == '\"' || line[i] == '\'')
		{
			while (line[++i] && line[i] != line[i - 1])
				i++;
		}
		else if (line[i] == '\\')
			i += 2;
		else
		{
			result++;
			i++;
		}
	}
	return (result);
}
