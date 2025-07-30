#include "varenv.h"

void	get_pid_var(int *i, char **temp, int *j)
{
	int	pid;

	pid = getpid();
	temp[*j] = ft_itoa(pid);
	i++;
	j++;
}
