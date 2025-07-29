/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimeter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 00:17:14 by kegonza           #+#    #+#             */
/*   Updated: 2025/07/29 12:37:15 by kegonza          ###   ########.fr       */
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

static void	process_delimiter(t_ctx *ctx)
{
	int	start;

	*(ctx->i) += 2;
	new_i(ctx->line, ctx->i, "spaces");
	start = *(ctx->i);
	new_i(ctx->line, ctx->i, "word");
	if (*(ctx->i) > start)
	{
		ctx->temp[*(ctx->j)] = ft_substr(ctx->line, start, *(ctx->i) - start);
		if (!ctx->temp[*(ctx->j)])
			return (here_doc_error(ctx->here_doc, "MALLOC"));
		if (*(ctx->j) == count_delimiters(ctx->line) - 1)
			ctx->here_doc->is_expandable = check_is_expandable
				(ctx->temp[*(ctx->j)]);
		ctx->temp[*(ctx->j)] = aux_get_delimiter(ctx->temp[*(ctx->j)]);
		if (!ctx->temp[*(ctx->j)])
			return (here_doc_error(ctx->here_doc, "PARSE"));
		(*(ctx->j))++;
	}
	if (*(ctx->i) > start && !ctx->temp[*(ctx->j) - 1])
		return (free_array(ctx->temp));
	ctx->temp[*(ctx->j)] = NULL;
}

static void	init_ctx(t_ctx *ctx, int *i, int *j, char **temp)
{
	ctx->i = i;
	ctx->j = j;
	ctx->temp = temp;
}

void	get_delimiters(char *line, t_heredoc *here_doc)
{
	int		i;
	int		j;
	char	**temp;
	t_ctx	*ctx;

	temp = malloc(sizeof(char *) * (count_delimiters(line) + 1));
	if (!temp)
		return (here_doc_error(here_doc, "MALLOC"));
	i = 0;
	j = 0;
	ctx = here_doc->ctx;
	init_ctx(ctx, &i, &j, temp);
	ctx->line = line;
	ctx->here_doc = here_doc;
	while (line[i] && line [i + 1])
	{
		if (line[i] == '<' && line[i + 1] && line[i + 1] == '<')
		{
			process_delimiter(ctx);
			continue ;
		}
		i++;
	}
	here_doc->delimiters = temp;
}
