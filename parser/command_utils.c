/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:25:18 by akwadran          #+#    #+#             */
/*   Updated: 2025/07/12 16:26:50 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	skip_delimit(char *aux, int *index)
{
	int	i;

	i = 0;
	while (ft_isspace(aux[i]))
		i++;
	while (aux[i] && !ft_isspace(aux[i]))
	{
		if (aux[i] == '\'' || aux[i] == '\"')
			i += close_quotes(&aux[i]);
		i++;
	}
	*index += i;
	return ;
}

void	get_infile(char *aux, int *index, char ***infile)
{
	char	*new_inf;
	int		i;

	i = 1;
	if (aux[i] == '<')
	{
		i++;
		skip_delimit(&aux[i], &i);
		*index += i;
	}
	else
	{
		new_inf = get_file_str(&aux[i], &i);
		*index += i;
	}
	if (*infile)
		*infile = append_file(*infile, new_inf);
	else
		*infile = first_file(new_inf);
}

char	**first_file(char *new_file)
{
	char	**file;

	file = (char **)malloc(sizeof(char *) * 2);
	if (!file)
		return (NULL);
	file[0] = new_file;
	file[1] = NULL;
	return (file);
}

char	**append_file(char **file, char *new_file)
{
	char	**res;
	char	**new_file_array;
	int		size;

	new_file_array = first_file(new_file);
	res = join_arrays(file, new_file_array);
	return (res);
}

void	get_outfile(char *aux, int *index, char ***outfile, int *append)
{
	char	*new_outf;
	int		i;

	i = 1;
	if (aux[i] == '>')
	{
		*append = 1;
		i++;
	}
	new_outf = get_file_str(&aux[i], &i);
	*index += i;
	if (*outfile)
		*outfile = append_file(*outfile, new_outf);
	else
		*outfile = first_file(new_outf);
}

char	*get_file_str(const char *aux, int *index)
{
	int	i;
	int	start;
	int	len;

	i = 0;
	while (ft_isspace(aux[i]))
		i++;
	start = i;
	while (aux[i] && !ft_isspace(aux[i]) && aux[i] != '>' && aux[i] != '<')
	{
		if (aux[i] == '\'' || aux[i] == '\"')
			i += close_quotes(&aux[i]);
		i++;
	}
	len = i - start;
	*index += i;
	return (ft_substr(aux, start, len));
}
