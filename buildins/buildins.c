#include "../data.h"
#include "../libft/libft.h"

void 	free_vars(void *args);
void 	show_vars(void *args);
void 	add_var(t_data *data_program, t_vars *new);
t_vars 	*new_var(char *name, char *value, int is_exportable);
t_vars	*search_var(t_data *data_program, char *name);
void init_env(t_data *data_program, char **env);
int count_exportable_vars(t_data *data_program);
t_vars **export_vars(t_data *data_program);
void example_new_vars(t_data *data_program);
int ft_strcmp(const char *s1, const char *s2);

void ft_cd(t_data *data_program);
void ft_export(t_data *data_program);
void ft_unset(t_data *data_program);
void ft_exit(t_data *data_program);

void	ft_pwd(t_data *data_program)
{
	t_vars	*tmp;

	tmp = search_var(data_program, "PWD");
	if (!tmp)
	{
		printf("Variable PWD not found\n");
		return ;
	}
	printf("%s\n", tmp->value);
}

char *pre_echo(char *var)
{
	char *name;
	int size;
	int i;

	i = 0;
	size = 0;
	while (var[size] && var[size] != ' ')
		size++;
	name = malloc(sizeof(char) * (size));
	if (!name)
		return (NULL);
	while (var[i] && var[i] != ' ')
	{
		name[i] = var[i + 1];
		i++;
	}
	name[i] = '\0';
	return (name);
}

void ft_echo(t_data *data_program, char *var)
{
	t_vars	*tmp;
	char	*value;
	char	*name;

	name = pre_echo(var);
	tmp = search_var(data_program, name);
	if (!tmp)
	{
		printf("Variable %s not found\n", var);
		return ;
	}
	value = tmp->value;
	if (value)
	{
		printf("%s\n", value);
	}
	else
	{
		printf("Variable %s is empty\n", var);
	}	
}

void	make_function(t_data *data_program, char *var)
{
	char	**args;
	int		i;

	printf("the line could be: %s\n", var);
	args = ft_split(var, ' ');
	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "echo") == 0)
		{
			printf("echo found\n");
			ft_echo(data_program, args[i + 1]);
			break;
		}
		// if (ft_strcmp(args[i], "cd") == 0)
		// {
		// 	printf("cd found\n");
		// 	ft_cd(data_program);
		// 	break;
		// }
		if (ft_strcmp(args[i], "pwd") == 0)
		{
			printf("pwd found\n");
			ft_pwd(data_program);
			break;
		}
		// if (ft_strcmp(args[i], "export") == 0)
		// {
		// 	printf("export found\n");
		// 	ft_export(data_program);
		// 	break;
		// }
		// if (ft_strcmp(args[i], "unset") == 0)
		// {
		// 	printf("unset found\n");
		// 	ft_unset(data_program);
		// 	break;
		// }
		// if (ft_strcmp(args[i], "env") == 0)
		// {
		// 	printf("env found\n");
		// 	show_vars(data_program);
		// 	break;
		// }
		// if (ft_strcmp(args[i], "exit") == 0)
		// {
		// 	printf("exit found\n");
		// 	ft_exit(data_program);
		// 	break;
		// }
		i++;
	}
	free(args);
}

int main(void)
{
	t_data *data_program;
	char *line1, *line2;

	data_program = malloc(sizeof(t_data));
	if (!data_program)
		return (1);
	add_var(data_program, new_var("MY_VAR", "Hello World", 1));
	add_var(data_program, new_var("PWD", "/home/user", 1));
	printf("<<------------------ Variables ------------------>>\n");
	show_vars(data_program);
	printf("\n<<-------------- end var's list --------------->>\n");
	line1 = ft_strdup("echo $MY_VAR");
	make_function(data_program, line1);
	free(line1);
	line2 = ft_strdup("pwd");
	make_function(data_program, line2);
	free(line2);
	free(data_program);
	return (0);
}

// PARA COMPILAR:
// cc libft/libft.a vars/*.c buildins/*.c 

// str = "echo -n hola mundo esto es 42"
// 		0	1	2


// **args

// readline = echo -n "hola" | export $USERMsg = " hola"

// char **arg

// arg[0] = echo -n "hola"
// arg[1] = export $USERMsg = " hola"

// splitear

// arg[0][0] = "echo"
// arg[0][1] = "-n"
// arg[0][2] = ""hola mundo esto es 42"" > hola
