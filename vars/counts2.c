/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counts2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 00:04:02 by kegonza           #+#    #+#             */
/*   Updated: 2025/07/16 19:30:03 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "varenv.h"

int	count_vars(char *line)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (line[i])
	{
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
