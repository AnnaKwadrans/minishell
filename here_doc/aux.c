/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 00:12:26 by kegonza           #+#    #+#             */
/*   Updated: 2025/05/23 01:24:41 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"

char	*remove_trailing_newline(char *str)
{
	int		len;
	char	*new_str;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		len--;
	new_str = malloc(len + 1);
	if (!new_str)
	{
		free(str);
		return (NULL);
	}
	ft_strlcpy(new_str, str, len + 1);
	free(str);
	return (new_str);
}

void	here_doc_error(t_heredoc *here_doc, char *error_msg)
{
	if (error_msg)
	{
		if (ft_strcmp(error_msg, "EOF") == 0)
			printf("EOF detected\n");
		else if (ft_strcmp(error_msg, "SIGINT") == 0)
			printf("SIGINT detected\n");
		else if (ft_strcmp(error_msg, "MALLOC") == 0)
			printf("MALLOC ERROR\n");
		else if (ft_strcmp(error_msg, "PARSE") == 0)
			printf("Parse error near `\\n`\n");
	}
	else
		printf("EOF detected\n");
	printf("<<----- \t HERE_DOC MODE STOPPED \t ----->>\n");
	free_here_doc(here_doc);
	restore_signals();
}

void	free_here_doc(t_heredoc *here_doc)
{
	if (here_doc)
	{
		if (here_doc->delimiter)
			free(here_doc->delimiter);
		if (here_doc->buffer)
			free_array(here_doc->buffer);
		free(here_doc);
	}
}
