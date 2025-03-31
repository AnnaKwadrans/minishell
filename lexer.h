#ifndef LEXER_H
# define LEXER_H 
# include <stdlib.h>
# include <stdbool.h>

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

#endif