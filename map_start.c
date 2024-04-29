/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:00:16 by vmyshko           #+#    #+#             */
/*   Updated: 2024/04/12 15:13:26 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	get_line_len(char *line)
{
	int		len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		len--;
	return (len);
}

static int	add_to_map(t_game *game, char *line)
{
	int		i;
	char	**map_array;

	i = 0;
	if (game->map.height == 0)
		game->map.width = get_line_len(line);
	else if (game->map.width != get_line_len(line))
		return (ERROR_INVALID_MAP);
	map_array = (char **)malloc(sizeof(char *) * (game->map.height + 1));
	if (!map_array)
		return (ERROR_ALLOCATING_MEMORY);
	while (i < game->map.height)
	{
		map_array[i] = game->map.grid[i];
		i++;
	}
	map_array[game->map.height++] = line;
	free(game->map.grid);
	game->map.grid = map_array;
	return (0);
}

static int	check_line(t_game *game, char *line)
{
	if (line[0] == '\n' || line[0] == '\0')
	{
		return (ERROR_EMPTY_LINE);
	}
	return (add_to_map(game, line));
}

// status error : invalid map or memory allocation
int	map_start(t_game *game, char *map_file)
{
	int		fd;
	char	*line;
	int		status;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (ERROR_OPENING_FILE);
	line = get_next_line(fd);
	while (line != NULL)
	{
		status = check_line(game, line);
		if (status != 0)
		{
			free(line);
			close(fd);
			return (status);
		}
		line = get_next_line(fd);
	}
	close(fd);
	return (validate_map(game));
}

char	*init_array(t_game *game)
{
	char	*array;

	array = (char *)malloc(sizeof(char) * game->map.width * game->map.height);
	if (!array)
		return (NULL);
	ft_memset(array, 0, game->map.width * game->map.height);
	return (array);
}
