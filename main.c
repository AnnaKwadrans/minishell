/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 20:29:42 by akwadran          #+#    #+#             */
/*   Updated: 2025/07/28 14:48:10 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "parser/parser.h"
#include "executor/executor.h"
#include "vars/varenv.h"

int	g_signal = 0;

char	*get_input(t_data *data)
{
	char	*input;

	if (data->is_interactive)
	{
		input = readline("minishell > ");
		if (input && *input)
			add_history(input);
	}
	else
		input = get_next_line(STDIN_FILENO);
	return (input);
}

void	initial_config(t_data *data, char **envp)
{
	init_data(data);
	init_env(data, envp);
	update_shlvl(data);
}

int	get_and_process_input(t_data *data_program, char **input)
{
	*input = get_input(data_program);
	if (!*input)
		return (0);
	if (g_signal == SIGINT)
	{
		data_program->last_status = 130;
		g_signal = 0;
		if (!*input)
		{
			free(input);
			return (2);
		}
	}
	if (*input && (*input)[0] == '\n')
		add_history(*input);
	if (!input[0])
		data_program->last_status = 0;
	return (1);
}

void	closing(t_data *data_program)
{
	int	status;

	write(1, "exit\n", 5);
	status = data_program->last_status;
	free_data(data_program);
	free(data_program);
	exit(status);
}

int	main(int argc, char **argv, char **envp)
{
	char			*input;
	static t_data	*data_program;
	int				status;

	(void)argc;
	(void)argv;
	data_program = malloc(sizeof(t_data));
	if (!data_program)
		return (1);
	initial_config(data_program, envp);
	while (1)
	{
		status = get_and_process_input(data_program, &input);
		if (!status)
			closing(data_program);
		if (status == 2)
			continue ;
		parse_data(input, data_program, envp);
		execute_line(data_program);
		if (data_program->is_expandable == 0)
			update_env(data_program);
		clean_data_program(data_program);
		free(input);
	}
}
