/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counts1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 00:04:02 by kegonza           #+#    #+#             */
/*   Updated: 2025/07/16 19:29:49 by akwadran         ###   ########.fr       */
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
