/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 00:12:26 by kegonza           #+#    #+#             */
/*   Updated: 2025/07/18 11:51:53 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"

int	count_outfiles(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '>')
		{
			count++;
			if (line[i + 1] == '>')
				i++;
		}
		i++;
	}
	return (count);
}

int	new_i(char *line, int *i, char *mode)
{
	if (!line || !mode)
		return (*i);
	if (ft_strcmp(mode, "spaces") == 0)
	{
		while (line[*i] && (line[*i] == ' ' || line[*i] == '\t'))
			(*i)++;
	}
	else if (ft_strcmp(mode, "quotes") == 0)
	{
		while (line[*i] && line[*i] != '"' && line[*i] != '\'')
			(*i)++;
	}
	else if (ft_strcmp(mode, "end") == 0)
	{
		while (line[*i] && line[*i] != '>' && line[*i] != '<')
			(*i)++;
	}
	else if (ft_strcmp(mode, "word") == 0)
	{
		while (line[*i] && line[*i] != ' ' && line[*i] != '\t'
			&& line[*i] != '>' && line[*i] != '<')
			(*i)++;
	}
	return (*i);
}

char	*remove_trailing_newline(char *str)
{
	int		len;
	char	*new_str;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		len--;
	new_str = malloc(len + 1);
	if (!new_str)
	{
		free(str);
		return (NULL);
	}
	ft_strlcpy(new_str, str, len + 1);
	free(str);
	return (new_str);
}

void	here_doc_error(t_heredoc *here_doc, char *error_msg)
{
	if (error_msg)
	{
		if (ft_strcmp(error_msg, "EOF") == 0)
			printf("EOF detected\n");
		else if (ft_strcmp(error_msg, "SIGINT") == 0)
			printf("SIGINT detected\n");
		else if (ft_strcmp(error_msg, "MALLOC") == 0)
			printf("MALLOC ERROR\n");
		else if (ft_strcmp(error_msg, "PARSE") == 0)
			printf("Parse error near `\\n`\n");
		else if (ft_strcmp(error_msg, "EXPAND_VARS") == 0)
			printf("Error expanding variables\n");
		else
			printf("Unknown error: %s\n", error_msg);
	}
	else
		printf("An error occurred in here_doc\n");
	if (here_doc)
		free_here_doc(here_doc);
}
