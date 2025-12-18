/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 21:59:42 by moel-idr          #+#    #+#             */
/*   Updated: 2025/12/18 08:49:07 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

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

void	handle_attack(t_game *g, t_torch *t)
{
	static int	last_mouse_state = 0;
	int			current_mouse_state;

	current_mouse_state = mlx_is_mouse_down(g->mlx, MLX_MOUSE_BUTTON_LEFT);
	if (current_mouse_state && !last_mouse_state && !t->is_attacking)
	{
		t->is_attacking = 1;
		t->attack_frame = 0;
	}
	last_mouse_state = current_mouse_state;
}

void	update_torch_animation(t_torch *t, t_game *g)
{
	double	movement;

	if (t->is_attacking)
	{
		t->attack_frame++;
		if (t->attack_frame >= 10)
		{
			t->is_attacking = 0;
			t->attack_frame = 0;
		}
		return ;
	}
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

void	draw_torch_pixel(t_game *g, t_torch *t, uint8_t *pixels, int img_width)
{
	uint32_t	pixel;

	t->idx = (t->orig_y * img_width + t->orig_x) * 4;
	t->r = pixels[t->idx + 0];
	t->g = pixels[t->idx + 1];
	t->b = pixels[t->idx + 2];
	t->alpha = pixels[t->idx + 3];
	if (t->alpha > 10)
	{
		t->screen_x = t->sprite_x + t->x;
		t->screen_y = t->sprite_y + t->y;
		if (t->screen_x >= 0 && t->screen_x < SCREEN_WIDTH && t->screen_y >= 0
			&& t->screen_y < SCREEN_HEIGHT)
		{
			pixel = (t->r << 24) | (t->g << 16) | (t->b << 8) | t->alpha;
			mlx_put_pixel(g->img, t->screen_x, t->screen_y, pixel);
		}
	}
}

void	draw_torch_sprite(t_game *g)
{
	static t_torch	t = {0, 0, 0, 0, 0.67, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0};
	uint8_t			*pixels;
	mlx_image_t		*current_img;

	handle_attack(g, &t);
	update_torch_animation(&t, g);
	if (t.is_attacking)
	{
		if (t.attack_frame < 5)
			current_img = g->img_attack1;
		else if (t.attack_frame < 10)
			current_img = g->img_attack2;
		else if (t.attack_frame < 15)
			current_img = g->img_attack1;
		else
			current_img = g->img_attack2;
	}
	else
		current_img = g->img_torch;
	t.sprite_width = (int)(current_img->width * t.scale);
	t.sprite_height = (int)(current_img->height * t.scale);
	t.sprite_x = (SCREEN_WIDTH - t.sprite_width) / 2;
	t.sprite_y = (SCREEN_HEIGHT - t.sprite_height + 30) + (int)t.bob;
	pixels = (uint8_t *)current_img->pixels;
	t.y = 0;
	while (t.y < t.sprite_height)
	{
		t.x = 0;
		while (t.x < t.sprite_width)
		{
			t.orig_x = (int)(t.x / t.scale);
			t.orig_y = (int)(t.y / t.scale);
			draw_torch_pixel(g, &t, pixels, current_img->width);
			t.x++;
		}
		t.y++;
	}
}
