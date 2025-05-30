#include <dirent.h>
#include <limits.h>
#include "../data.h"
#include "../libft/libft.h"
#include "../vars/varenv.h"
#include "../aux/aux.h"
#include "../executor.h"

int     ft_export()
{

}

static void    rm_first(t_vars **vars)
{
        t_vars  *temp;

        temp = *vars;
        *vars = (*vars)->next;
        free(temp->name);
        free(temp->value);
        temp->data = NULL;
        temp->next = NULL;
        printf("CHILD\n");
        ft_env(*vars);
}

static void    rm_last(t_vars *vars)
{
        t_vars  *temp;

        temp = vars;
        while (vars && vars->next)
        {
                if (!vars->next->next)
                {
                        free(vars->next->name);
                        free(vars->next->value);
                        vars->next->data = NULL;
                        vars->next = NULL;
                        printf("CHILD\n");
                        ft_env(temp);
                        return ;
                }
                vars = vars->next;
        }
}

static void    rm_middle(t_vars *vars, char *name)
{
        t_vars  *temp;
        
        while (vars && vars->next && vars->next->next)
        {
                if (strncmp(vars->next->name, name, ft_strlen(name)) == 0)
                {
                        temp = vars->next;
                        vars->next = vars->next->next;
                        free(temp->name);
                        free(temp->value);
                        temp->data = NULL;
                        temp->next = NULL;
                        printf("CHILD\n");
                        ft_env(vars);
                        return ;
                }
                vars = vars->next;
        }
        printf("CHILD\n");
        show_vars(vars);
}

int     ft_echo (char **args)
{
        int     i;
        int     size;

        if (ft_strncmp(args[1], "?", 1) == 0)
        {
                //printf("STATUS %d\n", ft_atoi(data->last_cmd->p_status));
                return (0);
        }
        size = array_size(args) - 1;
        i = 1;
        if (ft_strncmp(args[1], "-n", 2) == 0)
                i = 2;
        while (i < size)
        {
                printf("%s ", args[i]);
                i++;
        }
        printf("%s", args[i]);
        if (ft_strncmp(args[1], "-n", 2) != 0)
        printf("\n");
        return (0);
}

int     ft_unset(t_vars *vars, char **args)
{
        int     i;
        t_vars  *start;

        if (!vars || !args)
                return (ft_putendl_fd("not enough arguments", 2), 0);
        start = vars;
        i = 1;
        while (args[i])
        {
                if (ft_strncmp(args[i], vars->name, ft_strlen(args[i])) == 0)
                {

                        return (rm_first(&vars), 0);
                }
                while (vars && vars->next && vars->next->next)
                {
                        if (ft_strncmp(args[i], vars->next->name, ft_strlen(args[i])) == 0)
                        {

                                return (rm_middle(start, args[i]), 0);
                        }
                        vars = vars->next;
                }
                if (ft_strncmp(args[i], vars->next->name, ft_strlen(args[i])) == 0)
                {

                        return (rm_last(start), 0);
                }
                i++;
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
/*
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
        /*
        return (0);
}
*/