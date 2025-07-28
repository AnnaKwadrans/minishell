/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimeter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 00:17:14 by kegonza           #+#    #+#             */
/*   Updated: 2025/07/28 02:18:21 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"

int	count_delimiters(char *line)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '<' && line[i + 1] && line[i + 1] == '<')
		{
			i += 2;
			while (line[i] == ' ')
				i++;
			if (line[i] && line[i] != '<')
				count++;
		}
		else
			i++;
	}
	return (count);
}

char	*aux_get_delimiter(char *line)
{
	int		start;
	int		end;
	char	*temp;

	start = 0;
	while (line[start] != '\0' && (line[start] == '\''
			|| line[start] == '\"' || line[start] == ' '))
		start++;
	end = ft_strlen(line) - 1;
	while (end > start && (line[end] == ' '
			|| line[end] == '\'' || line[end] == '\"'))
		end--;
	if (end < start)
		return (free(line), NULL);
	temp = malloc(sizeof(char) * (end - start + 2));
	if (!temp)
		return (NULL);
	ft_strlcpy(temp, &line[start], end - start + 2);
	free(line);
	return (temp);
}

void	get_delimiters(char *line, t_heredoc *here_doc)
{
	int		i;
	int		j;
	int		start;
	char	**temp;
	int		count;

	count = count_delimiters(line);
	temp = malloc(sizeof(char *) * (count + 1));
	if (!temp)
		return (here_doc_error(here_doc, "MALLOC"));
	i = -1;
	j = 0;
	while (line[++i])
	{
		if (line[i] == '<' && line[i + 1] && line[i + 1] == '<')
		{
			i += 2;
			new_i(line, &i, "spaces");
			start = i;
			new_i(line, &i, "word");
			if (i > start)
				temp[j++] = aux_get_delimiter(ft_substr(line, start, i - start));
			if (i > start && !temp[j - 1])
				return (free_array(temp));
		}
	}
	temp[j] = NULL;
	here_doc->delimiters = temp;
	if (j > 0)
		here_doc->last_delimiter = temp[j - 1];
	else
		here_doc->last_delimiter = NULL;
	for (i = 0; temp[i]; i++)
		printf("Delimiter %d: '%s'\n", i, temp[i]);
	printf("last delimiter: '%s'\n", here_doc->last_delimiter);
}
