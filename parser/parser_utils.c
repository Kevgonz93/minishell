/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:53:45 by akwadran          #+#    #+#             */
/*   Updated: 2025/07/28 14:56:57 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	is_set(char c, char const *set)
{
	if (!set)
		return (0);
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

size_t	ft_strlen_set(const char *s, char *set)
{
	size_t	len;

	if (!s || !set)
		return (0);
	len = 0;
	while (s[len] && !is_set(s[len], set))
		len++;
	return (len);
}

char	*ft_strdup_set(const char *s, char *set)
{
	int		len;
	char	*ptr;

	if (!s || !set)
		return (NULL);
	len = ft_strlen_set(s, set) + 1;
	ptr = malloc(sizeof(char) * len);
	if (!ptr)
		return (ptr);
	ft_strlcpy(ptr, s, sizeof(char) * len);
	return (ptr);
}

char	*get_var(char *line)
{
	char	*name;
	char	*var;

	name = ft_strdup_set(line, " \t\n\v\r\f");
	var = getenv(name);
	free(name);
	return (var);
}

void	print_cmd(t_cmd **cmds)
{
	int	i;

	i = 0;
	while (cmds && cmds[i])
	{
		printf("\tCMD \t\t%d\n", i);
		printf("\tARGS\t");
		if (cmds[i]->args)
			print_array(cmds[i]->args);
		printf("\tINFILES\t");
		if (cmds[i]->infile)
		{
			print_array(cmds[i]->infile);
			printf("fd_in %d\n", cmds[i]->fd_in);
		}
		printf("\tOUTFILES\t");
		if (cmds[i]->outfile)
		{
			print_array(cmds[i]->outfile);
			printf("fd_out %d\n", cmds[i]->fd_out);
		}
		printf("\tAPPEND \t%d\n", cmds[i]->append);
		i++;
	}
}
