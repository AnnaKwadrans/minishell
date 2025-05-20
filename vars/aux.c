#include "varenv.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*joined;
	
	joined = ft_strjoin(s1, s2);
	free(s1);
	return (joined);
}

int ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

void	free_vars(void *args)
{
	t_vars	*var;
	t_vars	*next;
	t_data	*data_program;

	data_program = (t_data *)args;
	var = data_program->vars;
	while (var)
	{
		next = var->next;
		free(var->name);
		free(var->value);
		free(var);
		var = next;
	}
}

int mtrx_size(char **mtrx)
{
	int i = 0;
	while (mtrx[i])
		i++;
	printf("mtrx_size: %d\n", i);
	return (i);
}
