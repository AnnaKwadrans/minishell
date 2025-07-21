/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varenv1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:13:36 by akwadran          #+#    #+#             */
/*   Updated: 2025/07/18 01:01:04 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../data.h"
#include "../aux/aux.h"
#include "../libft/libft.h"
#include "../parser/parser.h"
#include "varenv.h"

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

static void	aux_init_env(t_data *data, t_vars *new_var)
{
	if (!data || !new_var)
		return ;
	new_var->is_exportable = 1;
	new_var->next = NULL;
	new_var->data = data;
	add_var(data, new_var);
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
		aux_init_env(data_program, new);
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

char	*handle_double_quotes(char *result, char *line, int *i, t_expand *exp)
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
