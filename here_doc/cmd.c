/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 00:33:55 by kegonza           #+#    #+#             */
/*   Updated: 2025/06/30 21:44:37 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"

static void	setup_heredoc_input(t_cmd *cmd)
{
	int	pipefd[2];
	int	i;

	if (pipe(pipefd) == -1)
		return (perror("pipe"), free_cmd(cmd));
	cmd->fd_in = pipefd[0]; // ← se usará como STDIN
	if (!cmd->heredoc || !cmd->heredoc->buffer || !cmd->heredoc->buffer[0])
	{
		// heredoc vacío: cerramos el write-end sin escribir nada
		close(pipefd[1]); // importante: esto permite que el reader reciba EOF
		return ;
	}
	i = 0;
	while (cmd->heredoc->buffer[i])
	{
		write(pipefd[1], cmd->heredoc->buffer[i],
			ft_strlen(cmd->heredoc->buffer[i]));
		write(pipefd[1], "\n", 1);
		i++;
	}
	close(pipefd[1]); // cerramos el write-end
}

static void	default_assign_cmd(t_cmd *cmd)
{
	printf("default assign cmd\n"); // para testear
	cmd->args = malloc(sizeof(char *) * 2);
	if (!cmd->args)
		return (free_cmd(cmd));
	cmd->args[0] = ft_strdup("cat");
	cmd->args[1] = NULL;
	setup_heredoc_input(cmd);
	return ;
}

static char	*get_arg(char *line, t_cmd *cmd)
{
	int		i;
	int		start;
	char	*args;
	char	*trim;

	i = 0;
	while (line[i] && (line[i] == ' ') || (line[i] == '\t'))
		i++;
	start = i;
	while (line[i] && line[i] != '<')
		i++;
	args = ft_substr(line, start, i - start);
	if (args)
	{
		trim = ft_strtrim(args, " \t");
		free(args);
		args = trim;
	}
	return (args);
}
void	get_heredoc_cmd(char *line, t_cmd *cmd)
{
	char	*args;

	args = get_arg(line, cmd);
	if (!args || !args[0])
	{
		if (args)
			free(args);
		default_assign_cmd(cmd);
	}
	else
	{
		cmd->args = ft_split(args, ' ');
		free(args);
		if (!cmd->args)
			return (free_cmd(cmd));
		printf("we got the cmd %s ", cmd->args[0]); // para testear
		if (cmd->args[1])
			printf("with the flags %s\n", cmd->args[1]); // para testear
		else
			printf("without flags\n"); // para testear
	}
	setup_heredoc_input(cmd);
	cmd->fd_out = STDOUT_FILENO;
	cmd->outfile = NULL;
	cmd->append = 0;
	cmd->infile = NULL;
	cmd->pid = 0;
	cmd->p_status = 0;
}
