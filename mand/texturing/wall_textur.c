/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_textur.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 23:09:01 by czghoumi          #+#    #+#             */
/*   Updated: 2025/12/21 11:36:48 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	draw_textured_wall(t_game *g, int x, t_ray *ray)
{
	t_calc			value;
	double			wall_x;
	mlx_texture_t	*tex;
	t_scalc			calc;

	if (!g)
		return ;
	value = refill(ray->perp_wall_dist);
	wall_x = wal_xx(ray, g);
	tex = wall_text(ray, g);
	if (ray->perp_wall_dist <= 0.0 || !tex)
	{
		draw_wall(g, x, ray);
		return ;
	}
	calc = calculatin(wall_x, tex, value);
	while (value.draw_start <= value.draw_end)
	{
		mlx_put_pixel(g->img, x, value.draw_start, color_pixwls_img(&calc,
				ray));
		value.draw_start++;
	}
}
