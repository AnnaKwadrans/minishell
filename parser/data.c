/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/06/30 21:48:07 by kegonza          ###   ########.fr       */
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
	data->vars = NULL;
	data->pipes = 0;
	data->is_interactive = isatty(STDIN_FILENO);
	if (data->is_interactive)
		setup_interactive_signals();
	else
		setup_nointeractive();
	data->is_expandable = 0;
	data->fds = NULL;
	data->last_status = 0;
}

void	parse_data(char *input, t_data *data, char **envp)
{
	printf("<<<-------------- NEW CMD -------------->>>\n");
	if (!valid_input(input, data))
		return ;
	// printf(">>>\t\tLINE: %s\n", data->line->line);
	//data->pipes = get_pipes(data->part_lines, array_size(data->part_lines));
	data->pipes = count_pipe(input);
	data->cmds = NULL;
	// data->cmds = malloc(sizeof(t_cmd *) * array_size(data->part_lines));
	//if (is_var(input))
	//	handle_var(input, data);
	//else
	//{
		data->cmds = parse_line(input, data->pipes, envp, data);
		//print_cmd(data->cmds);
		if (!data->cmds)
			return (free_data(data));
	//}
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
