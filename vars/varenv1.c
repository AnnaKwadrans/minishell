/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varenv1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:13:36 by akwadran          #+#    #+#             */
/*   Updated: 2025/07/16 19:38:30 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../data.h"
#include "../aux/aux.h"
#include "../libft/libft.h"
#include "../parser/parser.h"
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
		printf("\texportable: %d\n ", var->is_exportable);
		var = var->next;
		i++;
	}
}

void	init_env(t_data *data_program, char **env)
{
	int		i;
	char	**split;
	t_vars	*new;

	i = 0;
	while (env[i])
	{
		split = ft_split(env[i], '=');
		if (!split)
			return ;
		new = malloc(sizeof(t_vars));
		if (!new)
		{
			free_array(split);
			return ;
		}
		new->name = ft_strdup(split[0]);
		if (split[1])
			new->value = ft_strdup(split[1]);
		else
			new->value = NULL;
		new->is_exportable = 1;
		new->next = NULL;
		new->data = data_program;
		add_var(data_program, new);
		free_array(split);
		i++;
	}
}

char	*handle_single_quotes(char *result, char *line, int *i)
{
	(*i)++;
	while (line[*i] && line[*i] != '\'')
		result = ft_strjoin_free(result, (char []){line[(*i)++], '\0'});
	if (line[*i] == '\'')
		(*i)++;
	return (result);
}

char	*handle_double_quotes(char *result, char *line, int *i,
		t_expand *exp)
{
	(*i)++;
	while (line[*i] && line[*i] != '\"')
	{
		if (line[*i] == '$' && line[*i + 1] && line[*i + 1] != '$')
		{
			(*i)++;
			result = ft_strjoin_free(result, exp->values[(exp->count)++]);
			*i = skip_var(line, *i - 1);
		}
		else
			result = ft_strjoin_free(result, (char []){line[(*i)++], '\0'});
	}
	if (line[*i] == '\"')
		(*i)++;
	return (result);
}
