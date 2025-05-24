/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 00:18:04 by kegonza           #+#    #+#             */
/*   Updated: 2025/05/23 01:43:39 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"

int	is_here_doc(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '<')
		{
			if (line[i + 1] == '<' && line[i + 2] != '<')
				return (1);
			else
				return (0);
		}
		i++;
	}
	return (0);
}

int	check_is_expandable(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			return (0);
		i++;
	}
	return (1);
}
