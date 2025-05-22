#ifndef HERE_DOC_H
# define HERE_DOC_H
# include "../data.h"

void sigint_handler_heredoc(int sig);
void setup_heredoc_signals(void);
void restore_signals(void);
void free_here_doc(t_heredoc *here_doc);
char *remove_trailing_newline(char *str);
void here_doc_error(t_heredoc *here_doc, char *error_msg);
char **add_buffer(char **buffer, char *line);
int check_is_expandable(char *line);
char	*aux_get_delimiter(char *line);
void get_delimiter(char *line, t_heredoc *here_doc);
void	here_doc_init(char *line, t_heredoc *here_doc);
t_heredoc	*here_doc_mode(char *line);
int is_here_doc(char *line);

#endif