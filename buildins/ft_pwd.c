#include "builtins.h"

int	ft_pwd(void)
{
	char	path[PATH_MAX];

	if (getcwd(path, PATH_MAX) == NULL)
	{
		perror("getcwd failed");
		return (1);
	}
	printf("%s\n", path);
	return (0);
}