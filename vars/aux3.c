/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:13:36 by akwadran          #+#    #+#             */
/*   Updated: 2025/07/30 17:56:23 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../data.h"
#include "../aux/aux.h"
#include "../libft/libft.h"
#include "../parser/parser.h"
#include "varenv.h"

static char *expansion_loop_rm_quotes(char *line, char **vars,
		int *i, char *result, t_expand *exp)
{
    	if (line[*i] == '$' && line[*i + 1] && line[*i + 1] != '$')
		{
			(*i)++;
			result = ft_strjoin_free(result, vars[exp->count++]);
			*i = skip_var(line, *i - 1);
		}
		else if (line[*i] == '$' && line[*i + 1] == '$')
		{
			result = ft_strjoin_free(result, vars[exp->count++]);
			*i += 2;
		}
		else if ((line[*i] == '\'' || line[*i] == '\"'))
			result = handle_quotes(result, line, i, exp);
		else if (line[*i] == '\\' && line[*i + 1])
			result = ft_strjoin_free(result, (char []){line[(*i)++], '\0'});
		else
			result = ft_strjoin_free(result, (char []){line[(*i)++], '\0'});
        return (result);
}

static char *expansion_loop(char *line, char **vars,
		int *i, char *result, t_expand *exp)
{
    	if (line[*i] == '$' && line[*i + 1] && line[*i + 1] != '$')
		{
			(*i)++;
			result = ft_strjoin_free(result, vars[exp->count++]);
			*i = skip_var(line, *i - 1);
		}
		else if (line[*i] == '$' && line[*i + 1] == '$')
		{
			result = ft_strjoin_free(result, vars[exp->count++]);
			*i += 2;
		}
		else if (line[*i] == '\\' && line[*i + 1])
			result = ft_strjoin_free(result, (char []){line[(*i)++], '\0'});
		else
			result = ft_strjoin_free(result, (char []){line[(*i)++], '\0'});
        return (result);
}

char	*handle_expansion2(t_data *data, char *line, char **vars,
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
	
    if (rm_quotes)
    {
        while (line[i])
            result = expansion_loop_rm_quotes(line, vars, &i, result, &exp);
    }
    else
    {
        while (line[i])
            result = expansion_loop(line, vars, &i, result, &exp);
    }
	return (result);
}
