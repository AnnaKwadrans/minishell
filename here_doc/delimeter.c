/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimeter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 00:17:14 by kegonza           #+#    #+#             */
/*   Updated: 2025/07/13 20:43:23 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"

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
	return (temp);
}

void	get_delimiter(char *line, t_heredoc *here_doc)
{
	int		i;
	int		start;
	char	*temp;

	i = 0;
	start = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '<' && line[i + 1] == '<')
		{
			start = new_start(line);
			temp = malloc(sizeof(char) * (start - i + 1));
			if (!temp)
				return ;
			ft_strlcpy(temp, &line[i + 2], start - i);
			printf(">> temp is:%s\n", temp);
			here_doc->delimiter = aux_get_delimiter(temp);
			if (!here_doc->delimiter)
				return ;
			here_doc->is_expandable = check_is_expandable(temp);
			free(temp);
			return ;
		}
		i++;
	}
}
