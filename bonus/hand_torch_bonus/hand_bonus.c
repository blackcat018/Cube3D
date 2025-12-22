/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 21:59:42 by moel-idr          #+#    #+#             */
/*   Updated: 2025/12/22 10:14:23 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	update_torch_bob(t_torch *t, t_game *g)
{
	double	movement;

	movement = fabs(g->player.x - t->last_x) + fabs(g->player.y - t->last_y);
	if (movement > 0.001)
	{
		t->bob += 0.5 * t->bob_direction;
		if (t->bob >= 8.0 || t->bob <= -8.0)
			t->bob_direction = -t->bob_direction;
	}
	else
	{
		if (t->bob > 0)
			t->bob -= 0.5;
		else if (t->bob < 0)
			t->bob += 0.5;
		if (fabs(t->bob) < 0.5)
			t->bob = 0;
	}
	t->last_x = g->player.x;
	t->last_y = g->player.y;
}

void	draw_toch_continue(t_game *g, mlx_image_t *current_img, t_torch	t)
{
	float	dynamic_scale;
	uint8_t	*pixels;

	dynamic_scale = (float)g->screen_height / (current_img->height * 2.0f);
	t.sprite_width = (int)(current_img->width * dynamic_scale);
	t.sprite_height = (int)(current_img->height * dynamic_scale);
	t.sprite_x = (g->screen_width - t.sprite_width) / 2;
	t.sprite_y = (g->screen_height - t.sprite_height + 30) + (int)t.bob;
	pixels = (uint8_t *)current_img->pixels;
	t.y = 0;
	while (t.y < t.sprite_height)
	{
		t.x = 0;
		while (t.x < t.sprite_width)
		{
			t.orig_x = (int)(t.x / dynamic_scale);
			t.orig_y = (int)(t.y / dynamic_scale);
			draw_torch_pixel(g, &t, pixels, current_img->width);
			t.x++;
		}
		t.y++;
	}
}

void	draw_torch_sprite(t_game *g)
{
	static t_torch	t = {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0};
	mlx_image_t		*current_img;

	handle_attack(g, &t);
	handle_door_open(g, &t);
	update_torch_animation(&t, g);
	if (t.is_attacking)
	{
		if (t.attack_frame < 5)
			current_img = g->img_attack1;
		else
			current_img = g->img_attack2;
	}
	else if (t.is_opening)
	{
		if (t.open_frame < 4)
			current_img = g->img_open1;
		else
			current_img = g->img_open2;
	}
	else
		current_img = g->img_torch;
	draw_toch_continue(g, current_img, t);
}
