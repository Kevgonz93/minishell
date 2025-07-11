/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 00:17:36 by kegonza           #+#    #+#             */
/*   Updated: 2025/06/28 15:22:40 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "varenv.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*joined;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
	{
		joined = ft_strdup(s1);
		free(s1);
		return (joined);
	}
	joined = ft_strjoin(s1, s2);
	free(s1);
	return (joined);
}

void	free_vars(t_vars *vars)
{
	t_vars	*next;

	if (!vars)
		return ;
	while (vars)
	{
		next = vars->next;
		
		free(vars->name);
		vars->name = NULL;
		free(vars->value);
		vars->value = NULL;
		vars->data = NULL;
		vars->next = NULL;
		free(vars);
		vars = next;
	}
}

int	skip_var(const char *line, int i)
{
	i++;
	while (line[i] && (line[i] == '_' || ft_isalnum(line[i]) || line[i] == '?'))
		i++;
	return (i);
}

int	skip_quote(const char *line, int i)
{
	char	quote;

	// printf("Skip quote: %s\n", line);
	quote = line[i];
	while (line[i] && line[i] == quote)
		i++;
	return (i);
}
