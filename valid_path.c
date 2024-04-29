/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:03:10 by vmyshko           #+#    #+#             */
/*   Updated: 2024/04/12 15:56:27 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_position	make_pos(int x, int y)
{
	t_position	pos;

	pos.x = x;
	pos.y = y;
	return (pos);
}

static int	move(t_game *game, char *array, t_position pos, char element)
{
	int		i;

	i = pos.y * game->map.width + pos.x;
	if (game->map.grid[pos.y][pos.x] == element)
		return (1);
	if (array[i] || game->map.grid[pos.y][pos.x] == WALL)
		return (0);
	array[i] = 1;
	return (move(game, array, make_pos(pos.x + 1, pos.y), element)
		|| move(game, array, make_pos(pos.x - 1, pos.y), element)
		|| move(game, array, make_pos(pos.x, pos.y + 1), element)
		|| move(game, array, make_pos(pos.x, pos.y - 1), element));
}

static int	check_collectibles(t_game *game, char *array, char element, int res)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.grid[y][x] == element)
			{
				if (!move(game, array, make_pos(x, y), PLAYER))
				{
					res = 0;
					break ;
				}
			}
			ft_memset(array, 0, game->map.width * game->map.height);
			x++;
		}
		if (res == 0)
			break ;
		y++;
	}
	return (res);
}

static int	check_collectibles_all(t_game *game, char element)
{
	char	*array;
	int		result;

	array = init_array(game);
	if (!array)
		return (0);
	result = check_collectibles(game, array, element, 1);
	free(array);
	return (result);
}

int	validate_path(t_game *game, char element)
{
	char	*array;
	char	result;

	(void)element;
	result = 1;
	array = init_array(game);
	if (!array)
		return (ERROR_ALLOCATING_MEMORY);
	if (!check_collectibles_all(game, COLLECTIBLE))
		result = 0;
	if (!move(game, array, game->exit, PLAYER))
		result = 0;
	free(array);
	if (result == 0)
		return (ERROR_INVALID_PATH);
	return (0);
}
