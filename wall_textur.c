/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_textur.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czghoumi <czghoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 23:09:01 by czghoumi          #+#    #+#             */
/*   Updated: 2025/12/03 21:14:19 by czghoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

double	wal_xx(t_ray *ray, t_game *g)
{
	double	wall_x;
	double	perp;

	perp = ray->perp_wall_dist;
	if (ray->side == 0)
		wall_x = g->player.y + perp * ray->dir_y;
	else
		wall_x = g->player.x + perp * ray->dir_x;
	wall_x = wall_x - (int)wall_x;
	return (wall_x);
}

mlx_texture_t	*wall_text(t_ray *ray, t_game *g)
{
	mlx_texture_t	*tex;

	tex = NULL;
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			tex = g->texture_east; 
		else
			tex = g->texture_west; 
	}
	else
	{
		if (ray->dir_y > 0)
			tex = g->texture_south; 
		else
			tex = g->texture_north;
	}
	return (tex);
}

t_calc	refill(double perp)
{
	t_calc	ss;

	ss.line_height = (int)(SCREEN_HEIGHT / perp);
	ss.draw_start = -ss.line_height / 2 + SCREEN_HEIGHT / 2;
	if (ss.draw_start < 0) 
		ss.draw_start = 0;
	ss.draw_end = ss.line_height / 2 + SCREEN_HEIGHT / 2;
	if (ss.draw_end >= SCREEN_HEIGHT) 
		ss.draw_end = SCREEN_HEIGHT - 1;
	return (ss);
}

t_scalc	calculatin(double wall_x, mlx_texture_t *tex, t_calc value)
{
	t_scalc	ss;

	ss.pixels = (uint8_t *)tex->pixels;
	ss.tex_w = tex->width;
	ss.tex_h = tex->height;
	ss.tex_x = (int)(wall_x * (double)ss.tex_w);
	if (ss.tex_x < 0) 
		ss.tex_x = 0;
	if (ss.tex_x >= ss.tex_w) 
		ss.tex_x = ss.tex_w - 1;
	ss.step = (double)ss.tex_h / (double)value.line_height;
	ss.tex_pos = (value.draw_start - SCREEN_HEIGHT / 
			2.0 + value.line_height / 2.0) * ss.step;
	return (ss);
}

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
		mlx_put_pixel(g->img, x, value.draw_start, 
			color_pixwls_img(&calc, ray));
		value.draw_start++;
	}
}
