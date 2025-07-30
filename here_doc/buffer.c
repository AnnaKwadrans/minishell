/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:33:13 by kegonza           #+#    #+#             */
/*   Updated: 2025/07/30 18:04:52 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"

void	expand_buffer(t_heredoc *here_doc)
{
	int		i;

	if (!here_doc || !here_doc->buffer)
		return ;
	i = 0;
	while (here_doc->buffer[i])
	{
		here_doc->buffer[i] = expand_vars(NULL, here_doc->buffer[i], 0, 0);
		if (!here_doc->buffer[i])
			here_doc_error(here_doc, "EXPAND_VARS");
		i++;
	}
}

char	**add_buffer(char **buffer, char *line)
{
	int		count;
	int		i;
	char	**temp;

	count = 0;
	i = 0;
	while (buffer && buffer[count])
		count++;
	temp = malloc(sizeof(char *) * (count + 2));
	if (!temp)
		return (NULL);
	while (i < count)
	{
		temp[i] = ft_strdup(buffer[i]);
		if (!temp[i])
			return (free_array(temp), NULL);
		i++;
	}
	temp[count] = ft_strdup(line);
	temp[count + 1] = NULL;
	free_array(buffer);
	buffer = NULL;
	free(line);
	return (temp);
}
