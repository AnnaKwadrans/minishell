/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 20:29:42 by akwadran          #+#    #+#             */
/*   Updated: 2025/07/15 15:18:59 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "parser/parser.h"
#include "executor/executor.h"
#include "vars/varenv.h"

int	g_signal = 0; // Variable global para manejar SIGINT

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

int	main(int argc, char **argv, char **envp)
{
	char			*input;
	static t_data	*data_program;

	(void)argc;
	(void)argv;
	data_program = malloc(sizeof(t_data));
	initial_config(data_program, envp);
	while (1)
	{
		input = get_input(data_program);
		if (!input)
		{
			write(1, "exit\n", 5);
			clean_data_program(data_program);
			free(data_program);
			exit(data_program->last_status);
		}
		if (g_signal == SIGINT)
		{
			data_program->last_status = 130;
			g_signal = 0;
			if (!input || !*input)
			{
				free(input);
				continue ;
			}
		}
		if (input && *input)
			add_history(input);
		if (ft_strcmp(input, "") == 0)
			data_program->last_status = 0;
		parse_data(input, data_program, envp);
		execute_line(data_program);
		if (data_program->is_expandable == 0)
			update_env(data_program);
		clean_data_program(data_program);
		free(input);
	}
}

// PARA COMPILAR, APLICAR "-lreadline"
