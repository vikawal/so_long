/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:05:58 by vmyshko           #+#    #+#             */
/*   Updated: 2024/04/12 11:41:24 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//itearing through the map and calling the function
int	map_use(t_game *game, t_tile_function func)
{
	int	x;
	int	y;
	int	status;

	if (!game)
		return (ERROR_NULL_ARGUMENT);
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			status = func(game, x, y);
			if (status != 0)
				return (status);
			x++;
		}
		y++;
	}
	return (0);
}

static int	draw_tile(t_game *game, int x, int y)
{
	void	*img_tile;

	if (!game)
		return (-1);
	if (game->map.grid[y][x] == WALL)
		img_tile = game->tiles.wall;
	else
		img_tile = game->tiles.floor;
	mlx_image_to_window(game->mlx_ptr, img_tile, x * game->tile_size,
		y * game->tile_size);
	return (0);
}

static int	draw_tile_exit_collect(t_game *game, int x, int y)
{
	void	*img_tile;

	img_tile = NULL;
	if (!game)
		return (-1);
	if (game->map.grid[y][x] == COLLECTIBLE)
		img_tile = game->tiles.collectible;
	if (game->map.grid[y][x] == EXIT)
		img_tile = game->tiles.exit;
	if (img_tile)
		mlx_image_to_window(game->mlx_ptr, img_tile, x * game->tile_size,
			y * game->tile_size);
	return (0);
}

//draw whole map = render the game
void	map_draw(t_game *game)
{
	if (!game)
		exit (ERROR_NULL_ARGUMENT);
	map_use(game, draw_tile);
	map_use(game, draw_tile_exit_collect);
	mlx_image_to_window(game->mlx_ptr, game->tiles.player,
		game->player.x * game->tile_size,
		game->player.y * game->tile_size);
}

void	delete_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (game->textures[i] != NULL)
			mlx_delete_texture(game->textures[i]);
		i++;
	}
}
