#include "../parser.h"
#include "../data.h"

/*
int	ft_isspace(int c)
{
	if (c == ' ' || (c >= '\t' && c <= '\r'))
		return (1);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	i;

	if (size == 0)
		return (ft_strlen(src));
	i = 0;
	while (src[i] && i < (size - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
*/
bool	is_set(char c, char const *set)
{
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

	len = 0;
	while (s[len] && !is_set(s[len], set))
		len++;
	return (len);
}

char	*ft_strdup_set(const char *s, char *set)
{
	int		len;
	char	*ptr;

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
	//printf("%s\n", name);
	var = getenv(name);
	free(name);
	return(var);
}

t_lines	*last_line(t_lines *history_lines)
{
	t_lines	*last;

	if (!history_lines)
		return (NULL);
	last = history_lines;
	while (last->next)
		last = last->next;
	return (last);
}

