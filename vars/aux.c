/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonzal <kegonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 00:17:36 by kegonza           #+#    #+#             */
/*   Updated: 2025/07/30 17:22:42 by kegonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "varenv.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*joined;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
	{
		joined = ft_strdup(s1);
		free(s1);
		return (joined);
	}
	joined = ft_strjoin(s1, s2);
	free(s1);
	return (joined);
}

void	free_vars(t_vars *vars)
{
	t_vars	*next;

	if (!vars)
		return ;
	while (vars)
	{
		next = vars->next;
		free(vars->name);
		vars->name = NULL;
		free(vars->value);
		vars->value = NULL;
		vars->data = NULL;
		vars->next = NULL;
		free(vars);
		vars = next;
	}
}

int	skip_var(const char *line, int i)
{
	i++;
	while (line[i] && (line[i] == '_' || ft_isalnum(line[i]) || line[i] == '?'))
		i++;
	return (i);
}

int	skip_quote(const char *line, int i)
{
	char	quote;

	quote = line[i];
	if (line[i] == '\\')
		return (i + 2);
	while (line[i] && line[i] == quote)
		i++;
	return (i);
}

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
