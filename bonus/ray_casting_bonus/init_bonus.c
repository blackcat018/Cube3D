/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 10:08:11 by moel-idr          #+#    #+#             */
/*   Updated: 2025/12/22 10:13:09 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

double	clamp_light(double light)
{
	if (light < 0.1)
		return (0.1);
	if (light > 1.0)
		return (1.0);
	return (light);
}

void	init_ray(t_ray *ray, t_game *g, int x)
{
	ray->camera_x = 2 * x / (double)g->screen_width - 1;
	ray->dir_x = g->player.dir_x + g->player.plane_x * ray->camera_x;
	ray->dir_y = g->player.dir_y + g->player.plane_y * ray->camera_x;
	ray->map_x = (int)g->player.x;
	ray->map_y = (int)g->player.y;
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
	ray->hit = 0;
}

int	init_mouse(t_game *g)
{
	int32_t	center_x;
	int32_t	center_y;

	center_x = g->screen_width / 2;
	center_y = g->screen_height / 2;
	mlx_set_mouse_pos(g->mlx, center_x, center_y);
	return (0);
}
