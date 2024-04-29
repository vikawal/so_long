/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:03:31 by vmyshko           #+#    #+#             */
/*   Updated: 2024/04/12 11:43:50 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	check_argument(int argc, char **argv)
{
	char	*filename;
	int		len;

	if (argc != 2)
	{
		print_correct_error(ERROR_NO_MAP_FILE);
	}
	filename = argv[1];
	len = ft_strlen(filename);
	if (len < 4 || ft_strncmp((filename + len - 4), ".ber", 4) != 0)
	{
		print_correct_error(ERROR_INVALID_FILE_EXTENSION);
	}
}

static void	init_game_state(t_game *game)
{
	game->collectibles_count = 0;
	game->move_count = 0;
	game->map.grid = 0;
	game->map.height = 0;
	game->map.width = 0;
	game->map.collectibles = 0;
	game->exit.x = 0;
	game->exit.y = 0;
	game->player.x = 0;
	game->player.y = 0;
}

static void	player_movements(t_game *game)
{
	mlx_key_hook(game->mlx_ptr, moving_key_hook, game);
}

int	main(int argc, char *argv[])
{
	t_game	game;
	int		status;

	check_argument(argc, argv);
	init_game_state(&game);
	status = map_start(&game, argv[1]);
	if (status != 0)
	{
		free_game(&game);
		print_correct_error(status);
	}
	count_size_tiles(&game, WINDOW_WIDTH, WINDOW_HEIGHT);
	game.mlx_ptr = mlx_init(game.tile_size * game.map.width,
			game.tile_size * game.map.height, "so_long", true);
	if (!game.mlx_ptr)
		ft_error_by_mlx();
	status = create_game_status_resize(&game);
	if (status != 0)
		print_correct_error(status);
	map_draw(&game);
	player_movements(&game);
	mlx_loop(game.mlx_ptr);
	free_game(&game);
	mlx_terminate(game.mlx_ptr);
	return (EXIT_SUCCESS);
}
