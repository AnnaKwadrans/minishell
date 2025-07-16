/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 00:04:39 by kegonza           #+#    #+#             */
/*   Updated: 2025/07/15 17:43:27 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERE_DOC_H
# define HERE_DOC_H

# include "../data.h"
# include "../aux/aux.h"
# include "../vars/varenv.h"
# include "../signals/signals.h"
# include "../parser/parser.h"

// AUX.C
char		*remove_trailing_newline(char *str);
void		here_doc_error(t_heredoc *here_doc, char *error_msg);
void		free_here_doc(t_heredoc *here_doc);
char		**outfile_heredoc(char *line, t_cmd *cmd);
int			count_outfiles(char *line);
int			new_i(char *line, int *i, char *mode);

// CHECK.C
int			is_here_doc(char *line);
int			check_is_expandable(char *line);

// DELIMETER.C
char		*aux_get_delimiter(char *line);
void		get_delimiter(char *line, t_heredoc *here_doc);

// HERE_DOC.C
char		**add_buffer(char **buffer, char *line);
void		here_doc_init(char *line, t_heredoc *here_doc);
t_heredoc	*here_doc_mode(t_data *data_program, char *line);

// CMD.C
void		get_heredoc_cmd(char *line, t_cmd *cmd);

// BUFFER.C

void		expand_buffer(t_heredoc *here_doc);
char		**add_buffer(char **buffer, char *line);

#endif
