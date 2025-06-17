#include <stdio.h>

// int ft_isalnum(int c)
// {
// 	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
// }

// int	is_valid_update(char **args)
// {
// 	int	i;
// 	int	j;

// 	if (!args || !args[0])
// 		return (0);
// 	i = 0;
// 	while (args[i])
// 	{
// 		printf("Checking argument: \"%s\"\n", args[i]);
// 		j = 0;
// 		while (args[i][j])
// 		{
// 			printf("Checking character: %c\n", args[i][j]);
// 			if (!ft_isalnum(args[i][j]) && args[i][j] != '_')
// 				return (0); // Invalid character in variable name
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (1); // All variable names are valid
// }

// int main(void)
// {
// 	char *str[] = {"valid_var", "another_valid_var", NULL};

// 	if (is_valid_update(str))
// 	{
// 		printf("The variable name is valid.\n");
// 	}
// 	else
// 	{
// 		printf("The variable name is invalid.\n");
// 	}
// }
