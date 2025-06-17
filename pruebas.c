#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

#include "data.h"

void	init_env(t_data *data_program, char **env);

// int	ft_echo(t_data *data, char **args)
// {
// 	int	i;
// 	int	size;
// 	int	is_expadable;

// 	is_expadable = 0;
// 	//arreglar esto en el pareso de variables
// 	if (ft_strncmp(args[1], "?", 1) == 0)
// 	{
// 		printf("STATUS %d\n", data->last_status);
// 		return (0);
// 	}
// 	size = array_size(args) - 1;
// 	i = 1;
// 	if (args[1][0] == '-' && args[1][1] == 'n')
// 		i = 2;
// 	while (i < size)
// 	{
// 		printf("%s ", args[i]);
// 		i++;
// 	}
// 	printf("%s", args[i]);
// 	if (!(args[1][0] == '-' && args[1][1] == 'n'))
// 		printf("\n");
// 	return (0);
// }

// int	main(int argc, char *argv[], char **env)
// {
// 	t_data	*data;
// 	char	**args;

// 	args = malloc(4 * sizeof(char *));
// 	if (!args)
// 	{
// 		perror("malloc");
// 		return (1);
// 	}
// 	printf("Initializing data structure...\n");
// 	args[0] = "echo";
// 	args[1] = "Hello";
// 	args[2] = "\"$USER\"";
// 	args[3] = NULL;
// 	printf("example_new_vars called...\n");
// 	data = malloc(sizeof(t_data));
// 	init_env(data, env);
// 	data->last_status = 0;
// 	// Llamada a la función ft_echo
// 	printf("Calling ft_echo...\n");
// 	ft_echo(data, args);
// 	// Verificar el estado final
// 	printf("Last status: %d\n", data->last_status);

// 	return 0;
// }
