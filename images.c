/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:22:27 by vmyshko           #+#    #+#             */
/*   Updated: 2024/04/12 14:21:45 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// static void	delete_textures(t_game *game)
// {
// 	int	i;

// 	i = 0;
// 	while (i < 5)
// 	{
// 		if (game->textures[i] != NULL)
// 			mlx_delete_texture(game->textures[i]);
// 		i++;
// 	}
// }

int	create_game_textures(t_game *game)
{
	game->textures[0] = mlx_load_png("textures/hujlo.png");
	game->textures[1] = mlx_load_png("textures/exit.png");
	game->textures[2] = mlx_load_png("textures/hero.png");
	game->textures[3] = mlx_load_png("textures/wall.png");
	game->textures[4] = mlx_load_png("textures/ground.png");
	if (!game->textures[0] || !game->textures[1]
		|| !game->textures[2] || !game->textures[3] || !game->textures[4])
	{
		delete_textures(game);
		return (ERROR_LOAD_TEXTURE);
	}
	game->tiles.collectible = mlx_texture_to_image(game->mlx_ptr,
			game->textures[0]);
	game->tiles.exit = mlx_texture_to_image(game->mlx_ptr, game->textures[1]);
	game->tiles.player = mlx_texture_to_image(game->mlx_ptr, game->textures[2]);
	game->tiles.wall = mlx_texture_to_image(game->mlx_ptr, game->textures[3]);
	game->tiles.floor = mlx_texture_to_image(game->mlx_ptr, game->textures[4]);
	delete_textures(game);
	return (0);
}

void	count_size_tiles(t_game *game, int width, int height)
{
	int	width_tile;
	int	height_tile;

	width_tile = width / game->map.width;
	height_tile = height / game->map.height;
	if (width_tile < height_tile)
		game->tile_size = width_tile;
	else
		game->tile_size = height_tile;
}

static void	change_tiles_size(t_game *game, int width, int height)
{
	count_size_tiles(game, width, height);
	mlx_resize_image(game->tiles.floor, game->tile_size, game->tile_size);
	mlx_resize_image(game->tiles.wall, game->tile_size, game->tile_size);
	mlx_resize_image(game->tiles.player, game->tile_size, game->tile_size);
	mlx_resize_image(game->tiles.exit, game->tile_size, game->tile_size);
	mlx_resize_image(game->tiles.collectible, game->tile_size, game->tile_size);
}

static void	change_window_size(int width, int height, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	mlx_delete_image(game->mlx_ptr, game->tiles.floor);
	mlx_delete_image(game->mlx_ptr, game->tiles.wall);
	mlx_delete_image(game->mlx_ptr, game->tiles.player);
	mlx_delete_image(game->mlx_ptr, game->tiles.exit);
	mlx_delete_image(game->mlx_ptr, game->tiles.collectible);
	create_game_textures(game);
	change_tiles_size(game, width, height);
	map_draw(game);
}

int	create_game_status_resize(t_game *game)
{
	int	status;

	status = create_game_textures(game);
	if (status != 0)
	{
		return (status);
	}
	change_tiles_size(game, game->mlx_ptr->width, game->mlx_ptr->height);
	mlx_resize_hook(game->mlx_ptr, change_window_size, game);
	return (0);
}
