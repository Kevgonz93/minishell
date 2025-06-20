#include <dirent.h>
 #include <linux/limits.h>
#include <limits.h>
#include "../data.h"
#include "../libft/libft.h"
#include "../vars/varenv.h"
//#include "../aux/aux.h"
#include "../executor.h"

static t_vars	*export_new_var(char *arg)
{
	t_vars	*new;
	char	*name;
	char	*value;
	int		i;

	i = 0;
	name = ft_strdup_set(&arg[i], "=");
	while (arg[i] != '=')
		i++;
	value = ft_strdup_set(&arg[i + 1], " \t\n\v\r\f");
	new = new_var(name, value, 1);
	return (new);
}

int	ft_export(t_data *data, t_vars *vars, char **args)
{
	int		i;
	t_vars	*start;
	t_vars	*new;

	if (!vars || !args)
		return (ft_putendl_fd("not enough arguments", 2), 0);
	i = 1;
	start = vars;
	while (args[i])
	{
		while (vars)
		{
			if (ft_strncmp(args[i], vars->name, ft_strlen(args[i])) == 0)
			{
				vars->is_exportable = 1;
				break ;
			}
			vars = vars->next;
		}
		new = export_new_var(args[i]);
		add_var(data, new);
		i++;
		vars = start;
	}
}
/*
t_vars  *exp_new_var(t_data *data, char *name)
{
        t_vars	*var;
        char    *var_name;
        char    *var_value;
        int     i;

        i = 0;
        while (ft_isspace(name[i]))
                i++;
        var_name = ft_strdup_set(&name[i], "=");
        while (name[i] != '=')
                i++;
        var_value = ft_strdup_set(&name[i + 1], " \t\n\v\r\f");
        var = new_var(var_name, var_value, 1);
	var->is_exportable = 1;
        add_var(data, var);
        return (var);
}

int     ft_export(t_data *data, char *name)
{
        t_vars  *temp;
        t_vars  *new;

        temp = data->vars;
        while (temp)
        {
                if (ft_strncmp(name, temp->name, ft_strlen(name)) == 0)
                {
                        temp->is_exportable = 1;
                        return (0);
                }
                temp = temp->next;
        }
        new = exp_new_var(data, name);
        add_var(data, new);
	return (0);
}
*/
static void	rm_first(t_vars **vars)
{
	t_vars	*temp;

	temp = *vars;
	*vars = (*vars)->next;
	free(temp->name);
	free(temp->value);
	temp->data = NULL;
	temp->next = NULL;
	// printf("CHILD\n");
	ft_env(*vars);
}

static void	rm_last(t_vars *vars)
{
	t_vars	*temp;

	temp = vars;
	while (vars && vars->next)
	{
		if (!vars->next->next)
		{
			free(vars->next->name);
			free(vars->next->value);
			vars->next->data = NULL;
			vars->next = NULL;
			// printf("CHILD\n");
			ft_env(temp);
			return ;
		}
		vars = vars->next;
	}
}

static void	rm_middle(t_vars *vars, char *name)
{
	t_vars	*temp;

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
			// printf("CHILD\n");
			ft_env(vars);
			return ;
		}
		vars = vars->next;
	}
	// printf("CHILD\n");
	show_vars(vars);
}

int	is_correct_flag(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] != '-')
		return (0);
	i++;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo (t_data *data, char **args)
{
	int	i;
	int	size;
	int	is_n_flag;

	if (!args[1])
	{
		printf("\n");
		return (0);
	}
	if (ft_strncmp(args[1], "?", 1) == 0)
	{
		printf("STATUS %d\n", data->last_status);
		return (0);
	}
	size = array_size(args) - 1;
	if (args[1])
		is_n_flag = is_correct_flag(args[1]);
	i = 1;
	if (is_n_flag)
		i = 2;
	while (i < size)
	{
		printf("%s ", args[i]);
		i++;
	}
	printf("%s", args[i]);
	if (!is_n_flag)
		printf("\n");
	return (0);
}

int	ft_unset(t_vars *vars, char **args)
{
	int		i;
	t_vars	*start;

	if (!vars || !args)
		return (ft_putendl_fd("not enough arguments", 2), 0);
	start = vars;
	i = 1;
	while (args[i])
	{
		if (ft_strncmp(args[i], vars->name, ft_strlen(args[i])) == 0)
		{
			rm_first(&vars);
			break ;
		}
		while (vars && vars->next && vars->next->next)
		{
			if (ft_strncmp(args[i], vars->next->name, ft_strlen(args[i])) == 0)
			{
				rm_middle(start, args[i]);
				break ;
			}
			vars = vars->next;
		}
		if (ft_strncmp(args[i], vars->next->name, ft_strlen(args[i])) == 0)
		{
			rm_last(start);
			break ;
		}
		i++;
	}
	return (0);
}

int	ft_pwd(void)
{
	char	path[PATH_MAX];

	if (getcwd(path, PATH_MAX) == NULL)
		return (perror("getcwd failed"), -1);
	printf("%s\n", path);
	return (0);
}

int	ft_env(t_vars *vars)
{
	if (!vars)
		return (ft_putendl_fd("no vars", 2) , -1);
	while (vars)
	{
		if (vars->is_exportable)
			printf("%s=%s\n", vars->name, vars->value);
		vars = vars->next;
	}
	return (0);
}

int	ft_cd(t_data *data, char **args)
{
	t_vars	*home_var;
	char	*home_path;

	if (array_size(args) > 2)
	{ /*err*/ }
	else if (array_size(args) == 1 || ft_strncmp(args[1], "~", 1) == 0)
	{
		home_var = search_var(data, "HOME");
		if (chdir(home_var->value) == -1)
			perror("chdir failed");
	}
	else 
	{
		if (chdir(args[1]) == -1)
			perror("chdir failed");
	}
	return (1);
}

void	ft_exit(t_data *data, char **args)
{
	exit(data->last_status);
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
