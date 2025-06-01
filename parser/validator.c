/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:54:15 by akwadran          #+#    #+#             */
/*   Updated: 2025/06/01 18:58:59 by akwadran         ###   ########.fr       */
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

bool	is_var(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	handle_var(char *input, t_data *data)
{
	t_vars	*var;
	char	*name;
	char	*value;
	int		i;	

	i = 0;
	while (ft_isspace(input[i]))
		i++;
	name = ft_strdup_set(&input[i], "=");
	while (input[i] != '=')
		i++;
	value = ft_strdup_set(&input[i + 1], " \t\n\v\r\f");
	var = new_var(name, value, 0);
	add_var(data, var);
}
