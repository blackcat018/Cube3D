/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czghoumi <czghoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 12:15:18 by moel-idr          #+#    #+#             */
/*   Updated: 2025/12/20 08:54:08 by czghoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

int	is_player_spawn(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	set_player_direction(t_player *player, char direction)
{
	const double	directions[4][4] = {
	{0.0, -1.0, 0.66, 0.0},
	{0.0, 1.0, -0.66, 0.0},
	{1.0, 0.0, 0.0, 0.66},
	{-1.0, 0.0, 0.0, -0.66} 
	};
	const char		dir_chars[4] = {'N', 'S', 'E', 'W'};
	int				i;

	i = 0;
	while (i < 4)
	{
		if (direction == dir_chars[i])
		{
			player->dir_x = directions[i][0];
			player->dir_y = directions[i][1];
			player->plane_x = directions[i][2];
			player->plane_y = directions[i][3];
			return ;
		}
		i++;
	}
}

void	set_player_position(t_player *player, int map_x, int map_y)
{
	player->x = map_x + 0.5;
	player->y = map_y + 0.5;
	player->move_speed = 0.05;
	player->rot_speed = 0.05;
}

void	init_player(t_player *player, t_game *g)
{
	int	i;
	int	j;

	i = 0;
	player->radius = 0.2;
	while (i < g->map_height)
	{
		j = 0;
		while (g->my_map->map[i][j])
		{
			if (is_player_spawn(g->my_map->map[i][j]))
			{
				set_player_position(player, j, i);
				set_player_direction(player, g->my_map->map[i][j]);
				return ;
			}
			j++;
		}
		i++;
	}
}
