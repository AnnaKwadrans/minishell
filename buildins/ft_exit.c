#include "builtins.h"

void	ft_exit(t_data *data, char **args)
{
	int	status;

	status = data->last_status;
	free_data(data);
	exit(status);
}
