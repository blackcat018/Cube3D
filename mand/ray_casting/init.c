/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 11:08:59 by moel-idr          #+#    #+#             */
/*   Updated: 2025/12/25 10:02:39 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	applay_info(t_player *player, t_direction dir)
{
	player->dir_x = dir.dir_x;
	player->dir_y = dir.dir_y;
	player->plane_x = dir.plane_x;
	player->plane_y = dir.plane_y;
}

void	init_mouves(t_player *player, t_game *g, int i, int j)
{
	t_direction	dir;

	player->x = j + 0.5;
	player->y = i + 0.5;
	if (g->my_map->map[i][j] == 'N')
		dir = (t_direction){0.0, -1.0, 0.66, 0.0};
	else if (g->my_map->map[i][j] == 'S')
		dir = (t_direction){0.0, 1.0, -0.66, 0.0};
	else if (g->my_map->map[i][j] == 'E')
		dir = (t_direction){1.0, 0.0, 0.0, 0.66};
	else if (g->my_map->map[i][j] == 'W')
		dir = (t_direction){-1.0, 0.0, 0.0, -0.66};
	else
		return ;
	applay_info(player, dir);
	player->move_speed = 0.05;
	player->rot_speed = 0.03;
}

void	init_player(t_player *player, t_game *g)
{
	int	i;
	int	j;

	i = 0;
	while (i < g->map_height)
	{
		j = 0;
		while (g->my_map->map[i][j])
		{
			if (g->my_map->map[i][j] == 'N' || g->my_map->map[i][j] == 'S'
				|| g->my_map->map[i][j] == 'E' || g->my_map->map[i][j] == 'W')
			{
				init_mouves(player, g, i, j);
				return ;
			}
			j++;
		}
		i++;
	}
}

void	init_ray(t_ray *ray, t_game *g, int x)
{
	ray->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	ray->dir_x = g->player.dir_x + g->player.plane_x * ray->camera_x;
	ray->dir_y = g->player.dir_y + g->player.plane_y * ray->camera_x;
	ray->map_x = (int)g->player.x;
	ray->map_y = (int)g->player.y;
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
	ray->hit = 0;
}

t_wall	get_wall(t_ray *ray)
{
	t_wall	w;

	w.start = -w.line_h / 2 + SCREEN_HEIGHT / 2;
	if (w.start < 0)
		w.start = 0;
	w.end = w.line_h / 2 + SCREEN_HEIGHT / 2;
	if (w.end >= SCREEN_HEIGHT)
		w.end = SCREEN_HEIGHT - 1;
	if (ray->side == 0)
		w.color = 0x000880FF;
	else
		w.color = 0x088000FF;
	return (w);
}
