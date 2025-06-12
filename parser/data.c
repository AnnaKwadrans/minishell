/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:49:39 by akwadran          #+#    #+#             */
/*   Updated: 2025/06/05 21:30:47 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"
#include "../data.h"
#include "../libft/libft.h"
#include "../vars/varenv.h"
#include <readline/readline.h>

void	init_data(t_data *data)
{
	data->line = NULL;
	data->cmds = NULL;
	data->history_lines = NULL;
	data->part_lines = NULL;
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

t_lines	*get_line(t_data *data, char *input)
{
	t_lines	*line;

	line = malloc(sizeof(t_lines));
	if (!line)
		return (perror("malloc failed"), NULL);
	line->line = ft_strdup(input);
	line->next = NULL;
	line->data = data;
	data->part_lines = split_pipes(input, ';');
	return (line);
}

void	parse_data(char *input, t_data *data, char **envp)
{
	char	**part_lines;
	int		l;
	int		c;

	part_lines = NULL;
	printf("<<<-------------- NEW CMD -------------->>>\n");
	if (!even_quotes(input))
	{}
		// err invalid syntax
	data->line = get_line(data, input);
	printf("\t>>>\t\tLINE: %s\n", data->line->line);
	data->pipes = get_pipes(data->part_lines, array_size(data->part_lines));
	data->cmds = malloc(sizeof(t_cmd *) * array_size(data->part_lines));
	if (!data->cmds)
		return (free_data(data));
	l = 0;
	c = 0;
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
}

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

bool	even_quotes(char *line)
{
	int	single_com;
	int	double_com;
	int	i;

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
	{
		// err invalid syntax
		return (0);
	}
	return (1);
}
