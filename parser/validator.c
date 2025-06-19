/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:54:15 by akwadran          #+#    #+#             */
/*   Updated: 2025/06/19 20:17:33 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../data.h"
#include "../parser.h"
#include "../executor.h"
#include "../vars/varenv.h"
#include <stdbool.h>

bool	valid_pipes(char *line)
{
	int		i;
	bool	pipe;

	pipe = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '|')
		{
			i++;
			while (ft_isspace(line[i]))
				i++;
			if (line[i] == '|')
				return (0);
		}
		i++;
	}
	return (1);
}


bool	even_quotes(char *line)
{
	int	single_com;
	int	double_com;
	int	i;

	i = 0;
	single_com = 0;
	double_com = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			single_com++;
		else if (line[i] == '\"')
			double_com++;
		i++;
	}
	if ((single_com % 2 != 0) || (double_com % 2 != 0))
		return (0);
	return (1);
}
