#include "data.h"
#include "parser.h"

void    exec_all_lines(t_data *data);
int	execute_line(t_cmd **cmds, int pipes, int *fds, int *last_status);
//void    single_child(t_cmd *cmd);
void	exec_cmd(t_cmd *cmd);
char	*get_path(char **cmd_tab, char **path_tab);
int     *create_pipes(int pipes);
void    close_fds(int *fds, int pipes, int wr, int rd);

// executer.c
//int     execute_line(t_cmd ***cmds, int *pipes);
//int     execute_pipes(t_cmd *cmd, int pipes, int index);
//int	    exec_cmd(t_cmd *cmd);
int     handle_infile(char *infile, char *delimit);
int     handle_outfile(char *outfile, int append);
int	exec_line(t_cmd ***cmds, int *pipes);
//void    first_child(t_cmd *cmd, int pipes, int *fds);
//void    new_child(t_cmd *cmd, int pipes, int *fds, int i);
//void    last_child(t_cmd *cmd, int pipes, int *fds);
//void    parent(t_cmd **cmds, int pipes, int *fds);
void    redirect(t_cmd *cmd, int pipes, int *fds, int i);
void    child(t_cmd *cmd, int pipes, int *fds, int i);
char	**vars_to_char(t_vars *vars);
char	*get_str_var(char *name, char *value);

// ft_cd.c
int     ft_env(t_vars *vars);
int    ft_pwd();
int     ft_unset(t_vars *vars, char **args);
int     ft_echo (char **args);
