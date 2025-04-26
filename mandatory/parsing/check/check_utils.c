#include "../../include/cub3d.h"

char	**copy_arr(char **array)
{
	int		i;
	int		y;
	char	**arr;

	i = 0;
	y = ft_lenarray(array);
	arr = malloc((y + 1) * sizeof(char *));
	while (array[i])
	{
		arr[i] = ft_strdup(array[i]);
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

void	put_err(char *str, t_data *s_map)
{
	free_all(s_map, 0);
	ft_putstrn_fd(str, 2);
	exit(EXIT_FAILURE);
}
