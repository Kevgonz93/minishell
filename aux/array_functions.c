#include "../parser/parser.h"
//#include "../data.h"
#include "aux.h"

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

void	print_array(char **array)
{
	int	i;

	if (!array)
	{
		printf("\n");
		return ;
	}
	i = 0;
	while (array[i])
	{
		if (i != 0)
			printf("\t\t");
		printf("\t%d >%s\n", i, array[i]);
		i++;
	}
}

size_t	array_size(char **array)
{
	size_t	size;

	size = 0;
	if (!array)
		return (0);
	while (array[size])
		size++;
	return (size);
}

char	**join_arrays(char **array, char **add)
{
	int	i;
	int	j;
	char	**joined;

	if (!array && !add)
		return (NULL);
	if (!array)
		return (add);
	if (!add)
		return (array);
	joined = malloc(sizeof(char **) * (array_size(array) + array_size(add) + 1));
	if (!joined)
		return (NULL);
	i = 0;
	while (array[i])
	{
		joined[i] = ft_strdup(array[i]);
		i++;
	}
	j = 0;
	while (add[j])
	{
		joined[i] = ft_strdup(add[j]);
		i++;
		j++;
	}
	joined[i] = NULL;
	return (joined);
}
