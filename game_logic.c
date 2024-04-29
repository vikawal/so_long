/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:41:51 by vmyshko           #+#    #+#             */
/*   Updated: 2024/04/10 11:41:13 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	moving_keys(mlx_key_data_t keydata, int *move_x, int *move_y)
{
	if ((keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W)
		&& keydata.action == MLX_PRESS)
		*move_y = -1;
	if ((keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S)
		&& keydata.action == MLX_PRESS)
		*move_y = 1;
	if ((keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_A)
		&& keydata.action == MLX_PRESS)
		*move_x = -1;
	if ((keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_D)
		&& keydata.action == MLX_PRESS)
		*move_x = 1;
}

static void	player_moving(t_game *game, int move_x, int move_y)
{
	int		new_x;
	int		new_y;

	new_x = game->player.x + move_x;
	new_y = game->player.y + move_y;
	if (game->map.grid[new_y][new_x] != WALL)
	{
		game->tiles.player->instances[0].x += move_x * game->tile_size;
		game->tiles.player->instances[0].y += move_y * game->tile_size;
		game->player.x = new_x;
		game->player.y = new_y;
		game->move_count++;
		ft_printf("Lady Victory made %d moves\n", game->move_count);
	}
}

static void	collecting_items(t_game *game)
{
	size_t	i;

	if (game->map.grid[game->player.y][game->player.x] == COLLECTIBLE)
	{
		i = 0;
		while (i < game->tiles.collectible->count)
		{
			if (game->tiles.collectible->instances[i].x
				== game->player.x * game->tile_size
				&& game->tiles.collectible->instances[i].y
				== game->player.y * game->tile_size)
			{
				if (game->tiles.collectible->instances[i].enabled)
				{
					game->collectibles_count++;
					ft_printf("Putin was f@cked %d times\n",
						game->collectibles_count);
					game->tiles.collectible->instances[i].enabled = 0;
					game->map.grid[game->player.y][game->player.x] = FLOOR;
				}
			}
			i++;
		}
	}
}

static void	game_exit(t_game *game)
{
	if (game->map.grid[game->player.y][game->player.x] == EXIT &&
		game->map.collectibles == game->collectibles_count)
	{
		ft_printf("FINISH! You have f@cked Putin %d times\n",
			game->collectibles_count);
		mlx_close_window (game->mlx_ptr);
	}
	else if (game->map.grid[game->player.y][game->player.x] == EXIT &&
		game->map.collectibles != game->collectibles_count)
		ft_printf("Nope! You have more Putins to f@ck!! GO ON!\n");
}

void	moving_key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;
	int		move_x;
	int		move_y;

	move_x = 0;
	move_y = 0;
	game = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		ft_printf("You've pressed ESC. WHY?? :( Bye...\n");
		mlx_close_window(game->mlx_ptr);
	}
	moving_keys(keydata, &move_x, &move_y);
	if (move_x != 0 || move_y != 0)
	{
		player_moving(game, move_x, move_y);
		collecting_items(game);
		game_exit(game);
	}
}
