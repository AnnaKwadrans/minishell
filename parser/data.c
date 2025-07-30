/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:24:23 by akwadran          #+#    #+#             */
/*   Updated: 2025/07/30 16:19:52 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	init_data(t_data *data)
{
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
	if (!valid_input(input, data))
	{
		data->last_status = 2;
		return ;
	}
	data->pipes = count_pipes(input);
	data->cmds = NULL;
	data->cmds = parse_line(input, data->pipes, envp, data);
	if (!data->cmds)
		return (clean_data_program(data));
}

int	count_pipes(char *line)
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
