/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 17:33:57 by vmyshko           #+#    #+#             */
/*   Updated: 2024/04/12 11:32:31 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_game(t_game *game)
{
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		free(game->map.grid[y]);
		y++;
	}
	free(game->map.grid);
}

const char	*choose_error_messages(int error)
{
	static const char	*error_messages[] = {
		"No error.\n",
		"Error: Null argument provided.\n",
		"Error: Opening file failed.\n",
		"Error: Allocating memory; malloc failed.\n",
		"Error: Invalid map.\n",
		"Error: Invalid character in map.\n",
		"Error: Invalid map boundary. Not surrounded by walls.\n",
		"Error: Invalid player: there must be ONE player.\n",
		"Error: Invalid exit: there must be ONE exit.\n",
		"Error: No file provided: program needs ONE .ber file.\n",
		"Error: Invalid file: NOT .ber extension.\n",
		"Error: Invalid map: no player.\n",
		"Error: Invalid map: no exit.\n",
		"Error: Invalid map: no collectible.\n",
		"Error: Failure with loading game texture(s).\n",
		"Error: Invalid map path:impossible get all collectibles and exit.\n",
		"Error: Empty line in the map.\n"
	};

	return (error_messages[error]);
}

const char	*right_error_message(int error)
{
	if (error >= 0 && error < LAST_ERROR)
		return (choose_error_messages(error));
	else
		return ("Unknown error.");
}

void	print_correct_error(int error)
{
	const char	*message;

	message = right_error_message(error);
	ft_printf("%s", message);
	exit(EXIT_FAILURE);
}

void	ft_error_by_mlx(void)
{
	ft_printf("%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

// void	print_error(char *msg)
// {
// 	ft_printf("%s", msg);
// 	exit(EXIT_FAILURE);
// }
