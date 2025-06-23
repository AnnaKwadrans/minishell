/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:49:39 by akwadran          #+#    #+#             */
/*   Updated: 2025/06/23 22:43:00 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../data.h"
#include "../libft/libft.h"
#include "../vars/varenv.h"
#include <readline/readline.h>

void	init_data(t_data *data)
{
	data->line = NULL;
	data->cmds = NULL;
	data->history_lines = NULL;
	//data->part_lines = NULL;
	data->vars = NULL;
	data->pipes = 0;
	data->is_interactive = isatty(STDIN_FILENO);
	if (data->is_interactive)
		setup_interactive_signals();
	else
		setup_nointeractive();
	data->fds = NULL;
	data->last_status = 0;
}

void	parse_data(char *input, t_data *data, char **envp)
{
	printf("<<<-------------- NEW CMD -------------->>>\n");
	if (!input || input[0] == '\0')
	{
		printf("Empty input, returning...\n");
		return ;
	}
	if (input[0] == '\n' || input[0] == ' ')
	{
		printf("Input starts with newline or space, returning...\n");
		return ;
	}
	if (ft_strcmp(input, "\"\"" ) == 0 || ft_strcmp(input, "''") == 0)
	{
		printf("Input is empty quotes, returning...\n");
		return ;
	}
	if (!even_quotes(input))
	{
		printf("Invalid synax, returning...\n");
		free_data(data);
		return ;
	}
	if (!is_valid(input))
	{
		printf("Invalid syntax in input: %s\n", input);
		clean_data_program(data);
		return ;
	}
		// err invalid syntax
	data->line = get_line(data, input);
	// printf(">>>\t\tLINE: %s\n", data->line->line);
	//data->pipes = get_pipes(data->part_lines, array_size(data->part_lines));
	data->pipes = count_pipe(input);
	data->cmds = NULL;
	// data->cmds = malloc(sizeof(t_cmd *) * array_size(data->part_lines));
	if (is_var(input))
		handle_var(input, data);
	else
	{
		data->cmds = parse_line(input, data->pipes, envp, data);
		if (!data->cmds)
			return (free_data(data));
	}
/*	
	while (data->part_lines[l])
	{
		if (is_var(data->part_lines[l]))
		{
			handle_var(data->part_lines[l], data);
			l++;
		}
		else
		{
			data->cmds[c] = parse_line(data->part_lines[l], data->pipes[c],
				envp, data);
			if (!data->cmds[c])
				return (free_data(data));
			l++;
			c++;
		}
	}
	data->cmds[c] = NULL;
*/
}

t_lines	*get_line(t_data *data, char *input)
{
	t_lines	*line;

	line = malloc(sizeof(t_lines));
	if (!line)
		return (perror("malloc failed"), NULL);
	line->line = ft_strdup(input);
	line->next = NULL;
	line->data = data;
	//data->part_lines = split_pipes(input, ';');
	return (line);
}

int	count_pipe(char *line)
{
	int	pipes;
	int	i;

	pipes = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			i += close_quotes(&line[i]);
		if (line[i] == '|')
			pipes++;
		i++;
	}
	return (pipes);
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
	t_vars	*check;

	i = 0;
	while (ft_isspace(input[i]))
		i++;
	name = ft_strdup_set(&input[i], "=");

	while (input[i] != '=')
		i++;
	check = search_var(data, name);
	if (check)
	{
		free(check->value);
		check->value = ft_strdup_set(&input[i + 1], " \t\n\v\r\f");
	}
	else
	{
		value = ft_strdup_set(&input[i + 1], " \t\n\v\r\f");
		var = new_var(name, value, 0);
		add_var(data, var);
	}
}

/*
int	*get_pipes(char **part_lines, size_t size)
{
	int	*pipes;
	int	i;

	pipes = (int *)malloc(sizeof(int) * (size + 1));
	if (!pipes)
		return (NULL);
	i = 0;
	while (part_lines[i])
	{
		pipes[i] = count_pipe(part_lines[i]);
		i++;
	}
	pipes[size] = -1;
	return (pipes);
}
*/


