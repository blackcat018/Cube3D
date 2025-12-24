/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_n_color_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 11:00:13 by moel-idr          #+#    #+#             */
/*   Updated: 2025/12/23 14:43:12 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

uint32_t	color_pixwls_img(t_scalc *calc, t_ray *ray)
{
	int		tex_y;
	t_rgb	col;
	uint8_t	a;
	int		idx;

	tex_y = (int)calc->tex_pos;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= calc->tex_h)
		tex_y = calc->tex_h - 1;
	calc->tex_pos += calc->step;
	idx = (tex_y * calc->tex_w + calc->tex_x) * 4;
	col.r = calc->pixels[idx + 0];
	col.g = calc->pixels[idx + 1];
	col.b = calc->pixels[idx + 2];
	a = calc->pixels[idx + 3];
	if (ray->side == 1)
	{
		col.r = col.r / 2;
		col.g = col.g / 2;
		col.b = col.b / 2;
	}
	return ((col.r << 24) | (col.g << 16) | (col.b << 8) | a);
}

uint32_t	apply_lighting(uint32_t color, double intensity)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	r = (color >> 24) & 0xFF;
	g = (color >> 16) & 0xFF;
	b = (color >> 8) & 0xFF;
	a = color & 0xFF;
	r = (uint8_t)(r * intensity);
	g = (uint8_t)(g * intensity);
	b = (uint8_t)(b * intensity);
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

double	get_light_intensity(double dist)
{
	double	light;

	light = 1.0 - (dist / LIGHT);
	if (light < 0.1)
		light = 0.1;
	if (light > 1.0)
		light = 1.0;
	return (light);
}

void	draw_texture_column(t_column *col, t_calc *v, t_scalc *c, t_ray *ray)
{
	uint32_t	color;
	double		light;

	light = get_light_intensity(ray->perp_wall_dist);
	while (v->draw_start <= v->draw_end)
	{
		color = color_pixwls_img(c, ray);
		color = apply_lighting(color, light);
		mlx_put_pixel(col->game->img, col->x, v->draw_start, color);
		v->draw_start++;
	}
}

int	init_texture_data(t_game *g, t_ray *ray, t_calc *v, t_scalc *c)
{
	double			wall_x;
	mlx_texture_t	*tex;

	if (ray->perp_wall_dist <= 0.0)
		return (0);
	*v = refill(ray->perp_wall_dist, g);
	wall_x = wal_xx(ray, g);
	tex = wall_text(ray, g);
	if (!tex)
		return (0);
	*c = calculatin(wall_x, tex, *v, g);
	return (1);
}
