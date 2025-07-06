#ifndef AUX_H
# define AUX_H

# include "../data.h"
# include "../libft/libft.h"

// 👇 Forward declaration
typedef struct s_cmd t_cmd;
typedef struct s_data t_data;

// ARRAY FUNCTIONS

size_t	array_size(char **array);
void	print_array(char **array);
void	free_array(char **array);
char	**join_arrays(char **array, char **add);

#endif
