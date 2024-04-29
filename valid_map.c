/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:26:11 by vmyshko           #+#    #+#             */
/*   Updated: 2024/04/12 16:03:39 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//checking if all parts are in the map

static int	check_player_1(t_game *game, int x, int y)
{
	char	position;

	position = game->map.grid[y][x];
	if (position == PLAYER)
	{
		if (game->player.x == 0 && game->player.y == 0)
		{
			game->player.x = x;
			game->player.y = y;
		}
		else
			return (ERROR_INVALID_PLAYER_COUNT);
	}
	return (0);
}

static int	check_exit(t_game *game, int x, int y)
{
	char	position;

	position = game->map.grid[y][x];
	if (position == EXIT)
	{
		if (game->exit.x == 0 && game->exit.y == 0)
		{
			game->exit.x = x;
			game->exit.y = y;
		}
		else
		{
			return (ERROR_INVALID_EXIT_COUNT);
		}
	}
	return (0);
}

static int	check_collectible(t_game *game, int x, int y)
{
	char	position;

	position = game->map.grid[y][x];
	if (position == COLLECTIBLE)
		game->map.collectibles++;
	return (0);
}

static int	check_wall_valid_characters(t_game *game, int x, int y)
{
	char	position;

	position = game->map.grid[y][x];
	if (position != FLOOR && position != WALL && position != COLLECTIBLE
		&& position != EXIT && position != PLAYER)
		return (ERROR_INVALID_CHARACTER);
	if (y == 0 || x == 0 || y == game->map.height - 1
		|| x == game->map.width - 1)
	{
		if (position != WALL)
		{
			return (ERROR_INVALID_BOUNDARY);
		}
	}
	return (0);
}

int	validate_map(t_game *game)
{
	int		status;

	if (game->map.width < 3 || game->map.height < 3)
		return (ERROR_INVALID_MAP);
	status = map_use(game, check_wall_valid_characters);
	if (status != 0)
		return (status);
	status = map_use(game, check_player_1);
	if (status != 0)
		return (status);
	if (game->player.x == 0 || game->player.y == 0)
		return (ERROR_NO_PLAYER);
	status = map_use(game, check_exit);
	if (status != 0)
		return (status);
	if (game->exit.x == 0 || game->exit.y == 0)
		return (ERROR_NO_EXIT);
	map_use(game, check_collectible);
	if (game->map.collectibles == 0)
		return (ERROR_NO_COLLECTIBLE);
	return (validate_path(game, COLLECTIBLE));
}
