/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:21:53 by vmyshko           #+#    #+#             */
/*   Updated: 2024/04/12 15:10:30 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "MLX42.h"
# include "LIBFT/libft.h"

// #define WIDTH 512
// #define HEIGHT 512
# define MAX_DIMENSION 1024
# define WINDOW_WIDTH 1366
# define WINDOW_HEIGHT 768

# define FLOOR '0'
# define WALL '1'
# define EXIT 'E'
# define COLLECTIBLE 'C'
# define PLAYER 'P'

typedef struct s_position
{
	int	x;
	int	y;
}				t_position;

typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
	int			collectibles;
}				t_map;

typedef struct s_tiles
{
	mlx_image_t	*wall;
	mlx_image_t	*floor;
	mlx_image_t	*exit;
	mlx_image_t	*collectible;
	mlx_image_t	*player;
}				t_tiles;

typedef struct s_game
{
	int				collectibles_count;
	int				move_count;
	t_map			map;
	t_position		player;
	t_position		exit;
	mlx_t			*mlx_ptr;
	void			*win_ptr;
	t_tiles			tiles;
	int				tile_size;
	mlx_texture_t	*textures[5];
}				t_game;

typedef int	(*t_tile_function)(t_game *, int, int);

int			validate_map(t_game *game);
int			validate_path(t_game *game, char element);
int			map_use(t_game *game, t_tile_function func);
int			map_start(t_game *game, char *map_file);
void		count_size_tiles(t_game *game, int width, int height);
void		map_draw(t_game *game);
int			create_game_status_resize(t_game *game);
void		free_game(t_game *game);
void		ft_error_by_mlx(void);
void		print_correct_error(int error);
void		moving_key_hook(mlx_key_data_t keydata, void *param);
int			create_game_textures(t_game *game);
void		delete_textures(t_game *game);
char		*init_array(t_game *game);

enum e_ErrorCodes
{
	ERROR_NONE,
	ERROR_NULL_ARGUMENT,
	ERROR_OPENING_FILE,
	ERROR_ALLOCATING_MEMORY,
	ERROR_INVALID_MAP,
	ERROR_INVALID_CHARACTER,
	ERROR_INVALID_BOUNDARY,
	ERROR_INVALID_PLAYER_COUNT,
	ERROR_INVALID_EXIT_COUNT,
	ERROR_NO_MAP_FILE,
	ERROR_INVALID_FILE_EXTENSION,
	ERROR_NO_PLAYER,
	ERROR_NO_EXIT,
	ERROR_NO_COLLECTIBLE,
	ERROR_LOAD_TEXTURE,
	ERROR_INVALID_PATH,
	ERROR_EMPTY_LINE,
	LAST_ERROR
};
// static mlx_image_t* image;
// int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
// void ft_hook(void* param);
// void ft_randomize(void* param);
// void ft_make_images(mlx_t *mlx);
#endif