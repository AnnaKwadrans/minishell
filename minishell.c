/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 20:39:41 by akwadran          #+#    #+#             */
/*   Updated: 2025/07/14 20:52:57 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "parser/parser.h"
#include "executor/executor.h"
#include "vars/varenv.h"
/*
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

t_data	*init_minishell(int argc, char **argv, char **envp)
{
	t_data	*data_program;

	(void)argc;
	(void)argv;
	data_program = malloc(sizeof(t_data));
	init_data(data_program);
	init_env(data_program, envp);
	update_shlvl(data_program);
	return (data_program);
}

void	minishell_loop(char *input, t_data *data_program, char **envp)
{


}

int	main(int argc, char **argv, char **envp)
{
	char			*input;
	static t_data	*data_program;

	data_program = init_minishell(argc, argv, envp);
	while (1)
	{
		if (data_program->is_interactive)
			input = readline("minishell > ");
		else
			input = get_next_line(STDIN_FILENO);
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
*/