/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:28:19 by akwadran          #+#    #+#             */
/*   Updated: 2025/07/12 16:28:33 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_here_doc(t_heredoc *here_doc)
{
	if (here_doc)
	{
		if (here_doc->delimiter)
			free(here_doc->delimiter);
		if (here_doc->buffer)
			free_array(here_doc->buffer);
		free(here_doc);
	}
}

void	clean_data_program(t_data *data)
{
	int	i;

	if (!data)
		return ;
	if (data->cmds)
	{
		free_cmds(data);
		data->cmds = NULL;
	}
	data->pipes = 0;
	if (data->fds)
	{
		free(data->fds);
		data->fds = NULL;
	}
	data->is_expandable = 0;
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	clean_data_program(data);
	if (data->vars)
	{
		free_vars(data->vars);
		data->vars = NULL;
	}
}

void	free_cmds(t_data *data)
{
	int	i;

	i = 0;
	if (!data || !data->cmds)
		return ;
	while (data->cmds[i])
	{
		free_cmd(data->cmds[i]);
		data->cmds[i] = NULL;
		i++;
	}
	free(data->cmds);
	data->cmds = NULL;
}

void	free_cmd(t_cmd	*cmd)
{
	if (!cmd)
		return ;
	free_array(cmd->args);
	cmd->args = NULL;
	if (cmd->infile)
	{
		free_array(cmd->infile);
		cmd->infile = NULL;
	}
	if (cmd->outfile)
	{
		free_array(cmd->outfile);
		cmd->outfile = NULL;
	}
	if (cmd->heredoc)
	{
		free_here_doc(cmd->heredoc);
		cmd->heredoc = NULL;
	}
	cmd->data = NULL;
	free(cmd);
	cmd = NULL;
}
