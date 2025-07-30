/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 00:17:33 by kegonza           #+#    #+#             */
/*   Updated: 2025/07/30 16:17:40 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "varenv.h"

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

char	*get_var_value(t_data *data_program, char *name)
{
	t_vars	*tmp;

	tmp = data_program->vars;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*fill_var_name(char *line, int start, int size)
{
	char	*var_name;
	int		i;

	var_name = malloc(sizeof(char) * (size + 1));
	if (!var_name)
		return (NULL);
	i = 0;
	while (i < size)
	{
		var_name[i] = line[start];
		i++;
		start++;
	}
	var_name[i] = '\0';
	return (var_name);
}

char	*fill_var_values(t_data *data_program, char *line, int start)
{
	int		var_size;
	char	*var_name;
	char	*var_value;

	var_size = get_var_size(line, start);
	var_name = fill_var_name(line, start, var_size);
	if (!var_name)
		return (NULL);
	if (ft_strncmp(var_name, "?", 1) == 0)
	{
		free(var_name);
		return (ft_itoa(data_program->last_status));
	}
	var_value = get_var_value(data_program, var_name);
	free(var_name);
	if (!var_value)
		return (NULL);
	return (ft_strdup(var_value));
}

char	**multi_search(t_data *data_program, char *line, int count)
{
	char	**temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	temp = malloc(sizeof(char *) * (count + 1));
	if (!temp)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] && line[i + 1] != '$')
		{
			temp[j++] = fill_var_values(data_program, line, i + 1);
			i = skip_var(line, i);
		}
		else if (line[i] == '$' && line[i + 1] == '$')
		{
			temp[j++] = ft_itoa(getpid());
			i += 2;
		}
		else if (line[i] == '\'')
			i = skip_quote(line, i);
		else if (line[i] == '\"' || line[i] == '\'')
			i = skip_quote(line, i);
		else if (line[i] == '\\')
			i += 2;
		else
			i++;
	}
	temp[j] = NULL;
	return (temp);
}
