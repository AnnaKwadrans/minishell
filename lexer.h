#ifndef LEXER_H
# define LEXER_H 

# include <stdlib.h>
# include <stdbool.h>
# include "libft/libft.h"

typedef struct s_data t_data;
typedef struct s_lines t_lines;
typedef struct s_cmd t_cmd;

typedef struct s_lex
{
	char	**cmds;
	char	*infile;
	char	*outfile;
}	t_lex;

char	*get_var(char *line);
/*
char	**get_tokens(char *line, t_lex *lex);
char	*get_infile(char *line);
*/
bool	is_set(char c, char const *set);
size_t	ft_strlen_set(const char *s, char *set);
char	*ft_strdup_set(const char *s, char *set);

//libft
int	ft_isspace(int c);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

int	count_pipes(char *line);
bool	even_comas(char *line);
char	*get_var(char *line);
void	free_data(t_data *data);
t_lines	*last_line(t_lines *history_lines);
void	init_data(t_data *data);
void	parse_data(char *input, t_data *data);
t_cmd	**parse_line(char *input, int pipes);

char	**split_pipes(char const *s, char c);
void	print_array(char **array);
t_cmd	*get_cmd(char *aux);
void	free_array(char **array);
int	close_quotes(char const *s);

char	*get_infile(char *aux, char *delimit);
char	*get_outfile(char *aux, int append);

#endif
