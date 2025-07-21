/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:54:15 by akwadran          #+#    #+#             */
/*   Updated: 2025/07/21 19:21:05 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	valid_input(char *input, t_data *data) // check si se libera todo bien
{
	if (!input || input[0] == '\0')
		return (printf("Empty input, returning...\n"), 0);
	if (input[0] == '\n' || input[0] == ' ')
	{
		printf("Input starts with newline or space, returning...\n");
		return (0);
	}
	if (ft_strcmp(input, "\"\"" ) == 0 || ft_strcmp(input, "''") == 0)
		return (printf("Input is empty quotes, returning...\n"), 0);
	if (!even_quotes(input) || !valid_pipes(input))
	{
		printf("Invalid synax, returning...\n");
		clean_data_program(data);
		return (0);
	}
	if (empty_input(input))
	{
		printf("Invalid syntax in input: %s\n", input);
		clean_data_program(data);
		return (0);
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

int	empty_input(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '\"' && !ft_isspace(str[i]))
			return (0);
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
