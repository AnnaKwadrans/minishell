/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varenv2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:13:36 by akwadran          #+#    #+#             */
/*   Updated: 2025/07/30 16:27:42 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../data.h"
#include "../aux/aux.h"
#include "../libft/libft.h"
#include "../parser/parser.h"
#include "varenv.h"

static char	*handle_quotes(char *result, char *line, int *i, t_expand *exp)
{
	if (line[*i] == '\'')
		return (handle_single_quotes(result, line, i));
	else if (line[*i] == '\"')
		return (handle_double_quotes(result, line, i, exp));
	return (result);
}

static char	*handle_expansion(t_data *data, char *line, char **vars,
		bool rm_quotes)
{
	char		*result;
	int			i;
	t_expand	exp;

	result = ft_strdup("");
	i = 0;
	exp.data = data;
	exp.values = vars;
	exp.count = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] && line[i + 1] != '$')
		{
			i++;
			result = ft_strjoin_free(result, vars[exp.count++]);
			i = skip_var(line, i - 1);
		}
		else if (line[i] == '$' && line[i + 1] == '$')
		{
			result = ft_strjoin_free(result, vars[exp.count++]);
			i += 2;
		}
		else if (rm_quotes && (line[i] == '\'' || line[i] == '\"'))
			result = handle_quotes(result, line, &i, &exp);
		else if (line[i] == '\\' && line[i + 1])
			result = ft_strjoin_free(result, (char []){line[i++], '\0'});
		else
			result = ft_strjoin_free(result, (char []){line[i++], '\0'});
	}
	return (result);
}

char	*expand_vars(t_data *data_program, char *line, bool rm_quotes,
	bool free_line)
{
	char	**vars;
	int		count;
	char	*result;

	count = count_vars(line);
	vars = multi_search(data_program, line, count);
	result = handle_expansion(data_program, line, vars, rm_quotes);
	free_array(vars);
	vars = NULL;
	if (free_line)
		free(line);
	return (result);
}
