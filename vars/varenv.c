/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 00:17:28 by kegonza           #+#    #+#             */
/*   Updated: 2025/05/21 19:55:42 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../data.h"
#include "../aux/aux.h"
#include "../libft/libft.h"
#include "../parser.h"
#include "varenv.h"

void	show_vars(void *args)
{
	t_vars	*var;
	t_data	*data_program;
	int		i;

	i = 1;
	data_program = (t_data *)args;
	var = data_program->vars;
	while (var)
	{
		printf("Variable %d:\n", i);
		printf("\tname: %s\n", var->name);
		printf("\tvalue: %s\n ", var->value);
		var = var->next;
		i++;
	}
}

void	init_env(t_data *data_program, char **env)
{
	int		i;
	char	**split;
	t_vars	*vars;
	t_vars	*new;

	vars = data_program->vars;
	i = 0;
	while (env[i])
	{
		split = ft_split(env[i], '=');
		new = malloc(sizeof(t_vars));
		new->name = ft_strdup(split[0]);
		if (split[1])
			new->value = ft_strdup(split[1]);
		new->is_exportable = 1;
		add_var(data_program, new);
		free_array(split);
		i++;
	}
}

static char	*handle_quotes(char *result, char *line, int *i)
{
	char	quote;

	quote = line[(*i)++];
	result = ft_strjoin_free(result, (char []){quote, '\0'});
	while (line[*i] && line[*i] != quote)
		result = ft_strjoin_free(result, (char []){line[(*i)++], '\0'});
	if (line[*i] == quote)
		result = ft_strjoin_free(result, (char []){line[(*i)++], '\0'});
	return (result);
}

static char	*handle_expansion(t_data *data, char *line, char **vars)
{
	char	*result;
	int		i;
	int		j;

	result = ft_strdup("");
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] && line[i + 1] != '$')
		{
			i++;
			result = ft_strjoin_free(result, vars[j++]);
			i = skip_var(line, i - 1);
		}
		else if (line[i] == '\'' || line[i] == '\"')
			result = handle_quotes(result, line, &i);
		else if (line[i] == '\\' && line[i + 1])
			result = ft_strjoin_free(result, (char []){line[i++], '\0'});
		else
			result = ft_strjoin_free(result, (char []){line[i++], '\0'});
	}
	return (result);
}

char	*expand_vars(t_data *data_program, char *line)
{
	char	**vars;
	int		count;
	char	*result;

	count = count_vars(line);
	vars = multi_search(data_program, line, count);
	result = handle_expansion(data_program, line, vars);
	free_array(vars);
	return (result);
}

// static void example_new_vars(t_data *data_program)
// {
// 	t_vars	*new_var1;
// 	t_vars	*new_var2;
// 	t_vars	*new_var3;
// 	t_vars	*new_var4;
// 	t_vars	*new_var5;

// 	new_var1 = new_var("MY_VAR", "Hello World", 1);
// 	new_var2 = new_var("MY_VAR2", "42", 0);
// 	new_var3 = new_var("MY_VAR3", "Hello", 1);
// 	new_var4 = new_var("MY_VAR4", "World", 0);
// 	new_var5 = new_var("MY_VAR5", "!", 1);
// 	add_var(data_program, new_var1);
// 	add_var(data_program, new_var2);
// 	add_var(data_program, new_var3);
// 	add_var(data_program, new_var4);
// 	add_var(data_program, new_var5);
// }

// int main(int argc, char **argv, char **env)
// {
// 	t_data	*data_program;
// 	t_vars	*var;
// 	t_vars	**exported_vars;

// 	data_program = malloc(sizeof(t_data));
// 	if (!data_program)
// 		return (1);
// 	data_program->vars = NULL;
// 	init_env(data_program, env);
// 	example_new_vars(data_program);
// 	// show_vars(data_program);
// printf("\n<<------------------ exportable");
// printf("vars-- -- -- -- -- -- -- -- -->>\n\n ");
	// 	// exported_vars = export_vars(data_program);
	// 	// if (!exported_vars)
	// 	// {
	// 	// 	printf("Error al exportar las variables\n");
	// 	// 	return (1);
	// 	// }
	// 	// for (int i = 0; exported_vars[i]; i++)
	// 	// {
	// 	// 	printf("Variable exportable %d:\n", i + 1);
	// 	// 	printf("\tname: %s\n", exported_vars[i]->name);
	// 	// 	printf("\tvalue: %s\n ", exported_vars[i]->value);
	// 	// }
	// 	printf("\n<<------------------ expand vars ------------------>>\n\n");
	// 	char *line = "expanding -$MY_VAR3-, -$MY_VAR4-, -$MY_VAR5-";
	// 	char *expanded_line = expand_vars(data_program, line);

	// 	if (expanded_line)
	// 	{
	// 		printf("Linea expandida: %s\n", expanded_line);
	// 		free(expanded_line);
	// 	}
	// 	else
	// 		printf("Error al expandir la linea\n");
	// 	// var = search_var(data_program, "PWD");
	// 	// if (var)
	// 	// 	printf("Variable encontrada: %s=%s\n", var->name, var->value);
	// 	// else
	// 	// 	printf("Variable no encontrada\n");
	// 	free_vars(data_program);
	// 	free(data_program);
	// 	return (0);
	// }

	// PARA PROBAR ESTAS FUNCIONES CON LIBFT
	// cc libft/libft.a vars/*.c
