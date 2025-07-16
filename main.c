/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 20:29:42 by akwadran          #+#    #+#             */
/*   Updated: 2025/07/16 19:08:52 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "parser/parser.h"
#include "executor/executor.h"
#include "vars/varenv.h"

int	g_signal = 0; // Variable global para manejar SIGINT

void	update_shlvl(t_data *data)
{
	t_vars	*shlvl;
	int		lvl;

	if (!data || !data->vars)
		return ;
	shlvl = search_var(data, "SHLVL");
	lvl = ft_atoi(shlvl->value) + 1;
	free(shlvl->value);
	shlvl->value = ft_itoa(lvl);
}

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
	if (!data_program)
		return (1);
	initial_config(data_program, envp);
	while (1)
	{
		input = get_input(data_program);
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
		{
			add_history(input);
			printf("DEBUGGING: added input to history\n");
		}
		if (ft_strcmp(input, "") == 0)
			data_program->last_status = 0;
		parse_data(input, data_program, envp);
		execute_line(data_program);
		printf("last status: %d\n", data_program->last_status);
		printf("is_expandable: %d\n", data_program->is_expandable);
		if (data_program->is_expandable == 0)
			update_env(data_program);
		printf("the new value of _ is %s\n", get_var_value(data_program, "_"));
		clean_data_program(data_program);
		free(input);
	}
}

// PARA COMPILAR, APLICAR "-lreadline"
