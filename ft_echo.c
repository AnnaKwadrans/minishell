#include "data.h"

void ft_echo(char **str)
{
	if (str[1][0] != '-' && str[1][1] != 'n')
		printf("%s\n", str[2]);
	printf("%s", str[2]);
}

void ft_selector_buildins(char **str)
{
	if (ft_strcmp(str[0], "echo"))
		ft_echo(str);
	else if( ft_strcmp(str[0], "pwd"))
		ft_pwd(str);
	else if( ft_strcmp(str[0], "cd"))
		ft_cd(str);
	else if (ft_strcmp(str[0], "export"))
		ft_export(str);
	else if (ft_strcmp(str[0], "unset"))
		ft_unset(str);
	else if (ft_strcmp(str[0], "env"))
		ft_env(str);
	else if (ft_strcmp(str[0], "exit"))
		ft_exit(str);
	else
		ft_no_buildins(str);
}

str = "echo -n hola mundo esto es 42"
		0	1	2


**args

readline = echo -n "hola" | export $USERMsg = " hola"

char **arg

arg[0] = echo -n "hola"
arg[1] = export $USERMsg = " hola"

splitear

arg[0][0] = "echo"
arg[0][1] = "-n"
arg[0][2] = ""hola mundo esto es 42"" > hola
