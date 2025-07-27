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
	bool	s_quote;
	bool	d_quote;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'' && !s_quote)
			s_quote = 1;
		else if (line[i] == '\"' && !d_quote)
			d_quote = 1;
		else if (line[i] == '\'' && s_quote)
			s_quote = 0;
		else if (line[i] == '\"' && d_quote)
			d_quote = 1;
		else if (line[i] == '<' && !s_quote && !d_quote)
		{
			if (line[i + 1] == '<' && line[i + 2] != '<')
				return (1);
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
