/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counts.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 00:04:02 by kegonza           #+#    #+#             */
/*   Updated: 2025/06/24 22:52:50 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "varenv.h"

int	total_vars(t_data *data_program)
{
	t_vars	*tmp;
	int		count;

	tmp = data_program->vars;
	count = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

int	get_var_size(char *line, int start)
{
	int	size;
	int	i;	

	size = 0;
	i = start;
	while (line[i])
	{
		if (line[i] == '_' || ft_isalnum(line[i]) || line[i] == '?')
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

int	mtrx_size(char **mtrx)
{
	int	i;

	i = 0;
	while (mtrx[i])
		i++;
	return (i);
}

int	count_vars(char *line)
{
	int	i;
	int	count;

	// printf("Count vars: %s\n", line);
	count = 0;
	i = 0;
	while (line[i])
	{
		// printf("line[%d]: %c\n",i, line[i]);
		if (line[i] == '$' && (line[i + 1] != '\0' && line[i + 1] != '$'))
		{
			count++;
			i = skip_var(line, i);
		}
		else if (line[i] == '\"' || line[i] == '\'')
			i = skip_quote(line, i);
		else if (line[i] == '\\')
			i += 2;
		else
			i++;
	}
	return (count);
}

int	size_total(char *line, char **values)
{
	int	result;
	int	i;
	int	j;

	result = 0;
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			result += ft_strlen(values[j++]);
			i = skip_var(line, i);
		}
		else if (line[i] == '\"' || line[i] == '\'')
			i = skip_quote(line, i);
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
