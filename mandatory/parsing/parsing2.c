#include "../include/cub3d.h"

static int	check_remaining(int *find, int x)
{
	while (x < 6)
	{
		if (find[x] != 1)
			return (ft_putstrn_fd("Error: path or color is invalid", 2),
				1);
		x++;
	}
	return (0);
}

static int	update_find(char c, int *find, int x)
{
	if (c == 'N')
		find[0]++;
	else if (c == 'S')
		find[1]++;
	else if (c == 'W')
		find[2]++;
	else if (c == 'E')
		find[3]++;
	else if (c == 'F')
		find[4]++;
	else if (c == 'C')
		find[5]++;
	else
		return (check_remaining(find, x));
	return (2);
}

void	join_and_update_line(char **ptr_line, char *c)
{
	char	*join_line;

	join_line = ft_strjoin(*ptr_line, c);
	free(*ptr_line);
	*ptr_line = ft_strdup(join_line);
	free(join_line);
}

int	check_and_update_find(char c, int *find)
{
	int	x;
	
	x = update_find(c, find, 0);
	if (x == 0)
		return (0);
	else if (x == 1)
		return (1);
	return (2);
}

int	process_line(char *c, char **ptr_line, int *find)
{
	int	result;

	result = check_and_update_find(c[0], find);
	if (result != 2)
		return (result);
	join_and_update_line(ptr_line, c);
	return (2);
}

static int	process_west_east(char **str, int i, t_data *data_struct)
{
	if (str[i][0] == 'W')
	{
		if (process_path(str, i, "WE", &(data_struct->we)))
			return (1);
	}
	else if (str[i][0] == 'E')
	{
		if (process_path(str, i, "EA", &(data_struct->ea)))
			return (1);
	}
	return (0);
}

static int	process_north_south(char **str, int i, t_data *data_struct)
{
	if (str[i][0] == 'N')
	{
		if (process_path(str, i, "NO", &(data_struct->no)))
			return (1);
	}
	else if (str[i][0] == 'S')
	{
		if (process_path(str, i, "SO", &(data_struct->so)))
			return (1);
	}
	return (0);
}

static int	process_path_wrapper(char **str, int i, t_data *data_struct)
{
	if (process_north_south(str, i, data_struct))
		return (1);
	if (process_west_east(str, i, data_struct))
		return (1);
	return (0);
}

static int	process_non_direction(t_data *data_struct, char *str_i)
{
	if (str_i[0] == 'F')
	{
		if (process_color(data_struct->f, str_i, "F"))
			return (1);
	}
	else if (str_i[0] == 'C')
	{
		if (process_color(data_struct->c, str_i, "C"))
			return (1);
	}
	return (0);
}

static int	read_path_color(t_data *data_struct, char **str, int i)
{
	while (str[i] && i <= 5)
	{
		if (process_path_wrapper(str, i, data_struct))
			return (1);
		else if (str[i][0] != 'N' && str[i][0] != 'S' && str[i][0] != 'W'
				&& str[i][0] != 'E')
		{
			if (process_non_direction(data_struct, str[i]))
				return (1);
		}
		i++;
	}
	return (0);
}

int read_map_data(char *line, int fd, t_data *data_struct)
{
    char *tmp;

    tmp = NULL;
    while (line)
    {
        tmp = _strjoin(tmp, line);
        if (tmp == NULL)
            put_err("Error: Invalid map", data_struct);
        free(line);
        line = get_next_line(fd);
    }
    data_struct->map = ft_split(tmp, "\n");
    free(tmp);
    return 0;
}

int read_path_and_color(char *ptr_line, t_data *data_struct)
{
    char **str;

    str = ft_split(ptr_line, "\n");
    if (read_path_color(data_struct, str, 0))
        return (free_2d_array(str), 1);
    free_2d_array(str);
    return 0;
}

int read_map(char *line, int fd, t_data *data_struct, char *ptr_line)
{
    if (read_path_and_color(ptr_line, data_struct))
        return 1;
    return read_map_data(line, fd, data_struct);
}