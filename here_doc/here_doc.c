/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 00:40:38 by kegonza           #+#    #+#             */
/*   Updated: 2025/06/04 21:34:27 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"

char	*expand_vars(t_data *data_program, char *str);
char	**ft_full_split(char *s, char c);
int		ft_strcmp(const char *s1, const char *s2);
void	rl_replace_line(const char *text, int clear_undo);

volatile sig_atomic_t g_heredoc_interrupted = 0;

//  sig_atomic_t
// 	•	Es un tipo definido por la biblioteca estándar de C (viene de <signal.h>).
// 	•	Es un tipo entero garantizado para poder ser accedido y modificado de forma atómica por una señal. 
//		Esto significa que el acceso no puede ser interrumpido, lo cual es importante cuando se trabaja con manejadores de señales (signal handlers).
// ⚠️ Si una señal interrumpe la ejecución del programa, puede modificar esta variable sin provocar un comportamiento indefinido.

// volatile
// 	•	Informa al compilador que la variable puede cambiar en cualquier momento 
//		fuera del control del flujo del programa (por ejemplo, desde un signal handler).
// 	•	Esto impide optimizaciones que podrían suponer que el valor no cambia “mágicamente”.
// En otras palabras, volatile dice: “compilador, no hagas suposiciones sobre esta variable”.
// Por ejemplo:
//
// int running = 1;
// while (running) { hacer algo... }
// El compilador podría asumir que running nunca cambia y podría optimizarlo así:
// while (1) { /* hacer algo... */ }
// PERO, si otra parte del programa modifica running, entonces esa optimización crearía un bucle infinito.

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
	if (buffer)
		free_array(buffer);
	return (temp);
}

void	here_doc_init(char *line, t_heredoc *here_doc)
{
	setup_heredoc_signals();
	get_delimiter(line, here_doc);
	if (!here_doc->delimiter)
		here_doc_error(here_doc, "PARSE");
	if (here_doc->delimiter)
		printf("delimeter is: %s\n", here_doc->delimiter);
	here_doc->buffer = NULL; // por el sg en add_buffer
}

t_heredoc *here_doc_mode(t_data *data_program, char *line)
{
	t_heredoc	*here_doc;
	char		*new_line;
	int			i;

	i = 0;
	here_doc = malloc(sizeof(t_heredoc));
	if (!here_doc)
		return (here_doc_error(here_doc, "MALLOC"), NULL);
	here_doc_init(line, here_doc);
	printf("here_doc->is_expandable: %d\n", here_doc->is_expandable);
	while (here_doc->delimiter)
	{
		write(1, "heredoc > ", 10);
		new_line = remove_trailing_newline(get_next_line(STDIN_FILENO));
		if (g_heredoc_interrupted)
			return (here_doc_error(here_doc, "SIGINT"), NULL);
		if (ft_strcmp(new_line, here_doc->delimiter) == 0 || !new_line)
			break ;
		here_doc->buffer = add_buffer(here_doc->buffer, new_line);
		if (!here_doc->buffer)
			return (here_doc_error(here_doc, "MALLOC"), NULL);
	}
	if (here_doc->buffer && here_doc->is_expandable)
	{
		i = 0;
		while (here_doc->buffer[i])
		{
			here_doc->buffer[i] = expand_vars(data_program, here_doc->buffer[i]);
			if (!here_doc->buffer[i])
				return (here_doc_error(here_doc, "EXPAND_VARS"), NULL);
			printf("buffer[%d]: %s\n", i, here_doc->buffer[i]);
			i++;
		}
	}
	if (new_line)
		free(new_line);
	return (here_doc);
}

/*

int main(void)
{
	char		*token; // LO QUE HAY ENTRE PIPES
	t_heredoc	*here_doc;
	t_cmd		*cmd;
	int i;

	while (1)
	{
		token = readline("test >");
		if (is_here_doc(token))
		{
			here_doc = here_doc_mode(token);
			if (!here_doc)
			{
				free(token);
				continue;
			}
			printf("\t !!! here should make execve !!!\n");
			if (here_doc->buffer && here_doc->buffer[0] != NULL)
			{
				i = 0;
				while (here_doc->buffer[i] != NULL)
				{

					printf("buffer[%d]: %s\n", i, here_doc->buffer[i]);
					i++;
				}
			}
			free(here_doc->buffer);
			free(here_doc->delimiter);
			free(here_doc);
		}
		else if (ft_strcmp(token, "exit") == 0 || !token)
		{
			printf("Exiting...\n");
			free(token);
			return (0);
		}
	}
}
*/
// PARA COMPILAR:
// cc aux/ft_full_split.c aux/array_functions.c libft/libft.a here_doc/here_doc.c -lreadline

// PENDIENTE:


// Detectar si el delimitador está en comillas simples, dobles o sin comillas.

// Si está en comillas simples, no se debe expandir.

	// cat << EOF
	// Hola $USER
	// Fecha: `date`
	// EOF

	// Hola tu_nombre_de_usuario
	// Fecha: Sun May 11 12:34:56 UTC 2025

	// •	Se expanden variables ($USER) y comandos (`date`).
	// •	El delimitador EOF puede estar en cualquier lugar mientras esté solo en una línea.

	// kev@MacBook-Air-de-Kevin minishell % cat << EOF
	// heredoc> hello $USER
	// heredoc> date: `date`
	// heredoc> EOF
	// hello kev
	// date: martes, 13 de mayo de 2025, 01:32:36 CEST

// Si está en comillas dobles, se debe expandir.

	// cat << "EOF"
	// Hola $USER
	// Fecha: `date`
	// EOF

	// Hola $USER
	// Fecha: `date`

	// •	No se expande nada.
	// •	El delimitador "EOF" debe coincidir exactamente con "EOF" 
	// 	(aunque el shell lo reconoce bien sin comillas al cerrar).

	// kev@MacBook-Air-de-Kevin minishell % cat << "EOF"
	// heredoc> hello $USER
	// heredoc> date `date`
	// heredoc> EOF
	// hello $USER
	// date `date`

// Si no está en comillas, se debe expandir.

// 	cat << 'EOF'
// 	Hola $USER
// 	Fecha: `date`
// 	EOF

// 	Hola $USER
// 	Fecha: `date`

// 	•	Igual que el anterior: nada se expande.
// 	•	'EOF' también hace que el delimitador sea interpretado literalmente.


// 	kev@MacBook-Air-de-Kevin minishell % cat << 'EOF'
// 	heredoc> hello $USER
// 	heredoc> date `date`
// 	heredoc> EOF
// 	hello $USER
// 	date `date`

// Entonces una vez obtenido el delimitador real, 
// deberíamos tener en cuenta si el buffer será expandible.
// Esto podríamos almacenarlo en una variable para saber si el buffer es expandible o no
// para luego ejecutar y/o expandirlo en la ejecución.

// ¿USAR UNA ESTRUCTURA PARA ELLO?

// Sí

// typedef struct s_heredoc
// {
// 	char	*delimiter;    // delimitador sin comillas
// 	int		quoted;        // 0 = expandible, 1 = literal (no expandir nada)
// 	char	**buffer;      // contenido del heredoc
// }	t_heredoc;

// FALTA CONSIDERAR QUE EXISTIRÁN LÍNEAS VACÍAS EN EL BUFFER
