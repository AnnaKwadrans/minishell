#include <dirent.h>
#include <limits.h>
#include "../data.h"
#include "../libft/libft.h"
#include "../vars/varenv.h"

int     ft_export()
{

}

static void    rm_var(t_vars *vars)
{
        t_vars  *temp;

        temp = vars->next;
        vars->next = vars->next->next;
        temp->next = NULL;
        free_vars(temp);
}

int     ft_unset(t_vars *vars, char **args)
{
        int     i;
        
        if (!vars || !args)
                return (ft_putendl_fd("not enough arguments", 2), 0);
        if (!vars->next)
        {
                i = 1;
                while (args[i])
                {
                        if (ft_strncmp(args[i], vars->name, ft_strlen(args[i])) == 0)
                                free_vars(vars->data);
                        i++;
                }
                return (0);
        }
        while (vars->next)
        {
                i = 1;
                while (args[i])
                {
                        if (ft_strncmp(args[i], vars->next->name, ft_strlen(args[i])) == 0)
                                rm_var(vars);
                        i++;
                }
                vars = vars->next;
        }
        return (0);
}

int    ft_pwd()
{
        char    path[PATH_MAX];

        if (getcwd(path, PATH_MAX) == NULL)
                return (perror("getcwd failed"), -1);
        printf("%s\n", path);
        return (0);
}

int     ft_env(t_vars *vars)
{
        if (!vars)
                return (ft_putendl_fd("no vars", 2) , -1);
        while (vars)
        {
                printf("%s=%s\n", vars->name, vars->value);
                vars = vars->next;
        }
        return (0);
}



void    ft_cd(char *path)
{
        opendir(path);
}

int main(int argc, char **argv, char **envp)
{
        char    *path = malloc(50);
        char    *path3;
        
        ft_pwd();
        //scanf("%s", path);
        //if (chdir(path) == -1)
        //        printf("fail");
        //else
        //        printf("success\n");
        /*path3 = getcwd(path2, 1024);
        if (path3 == NULL)
                printf("fail\n");
        else
                printf("3: %s\n", path3);
        printf("end :%s", path2);
        free(path);*/
        //free(path2);
        return (0);
}