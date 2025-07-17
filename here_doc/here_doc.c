/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 00:40:38 by kegonza           #+#    #+#             */
/*   Updated: 2025/07/16 20:39:51 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"

char	*expand_vars(t_data *data_program, char *str, bool rm_quotes,
			bool free_line);
char	**ft_full_split(char *s, char c);
int		ft_strcmp(const char *s1, const char *s2);
void	rl_replace_line(const char *text, int clear_undo);

void	here_doc_init(char *line, t_heredoc *here_doc)
{
	g_signal = 0;
	setup_heredoc_signals();
	get_delimiter(line, here_doc);
	if (!here_doc->delimiter)
		here_doc_error(here_doc, "PARSE");
	if (here_doc->delimiter)
		printf("delimeter is: %s\n", here_doc->delimiter);
	here_doc->buffer = NULL;
}

static void	finishing_here_doc(t_heredoc *here_doc, t_data *data_program)
{
	int	i;

	if (here_doc->buffer && here_doc->is_expandable)
	{
		i = 0;
		while (here_doc->buffer[i])
		{
			here_doc->buffer[i] = expand_vars(data_program, here_doc->buffer[i],
					1, 0);
			if (!here_doc->buffer[i])
				return (here_doc_error(here_doc, "EXPAND_VARS"));
			printf("buffer[%d]: %s\n", i, here_doc->buffer[i]);
			i++;
		}
	}
	if (data_program->is_interactive)
		setup_interactive_signals();
	else
		restore_signals();
}

t_heredoc	*here_doc_mode(t_data *data_program, char *line)
{
	t_heredoc	*here_doc;
	char		*new_line;

	new_line = NULL;
	here_doc = malloc(sizeof(t_heredoc));
	if (!here_doc)
		return (here_doc_error(here_doc, "MALLOC"), NULL);
	here_doc_init(line, here_doc);
	while (here_doc->delimiter)
	{
		write(1, "heredoc > ", 10);
		new_line = remove_trailing_newline(get_next_line(STDIN_FILENO));
		if (!new_line || g_signal
			|| ft_strcmp(new_line, here_doc->delimiter) == 0)
			break ;
		here_doc->buffer = add_buffer(here_doc->buffer, new_line);
		if (!here_doc->buffer)
			return (free(new_line), here_doc_error(here_doc, "MALLOC"), NULL);
		free(new_line);
		new_line = NULL;
	}
	if (g_signal)
		return (here_doc_error(here_doc, "SIGINT"), NULL);
	finishing_here_doc(here_doc, data_program);
	return (here_doc);
}
