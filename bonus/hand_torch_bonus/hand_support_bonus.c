/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand_support_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 09:58:56 by moel-idr          #+#    #+#             */
/*   Updated: 2025/12/22 10:14:19 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	handle_door_open(t_game *g, t_torch *t)
{
	static int	last_key_state;
	int			current_key_state;

	last_key_state = 0;
	current_key_state = mlx_is_key_down(g->mlx, MLX_KEY_E);
	if (current_key_state && !last_key_state && !t->is_opening
		&& !t->is_attacking)
	{
		t->is_opening = 1;
		t->open_frame = 0;
	}
	last_key_state = current_key_state;
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

void	continue_torch_anim(t_torch *t, t_game *g)
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

void	update_torch_animation(t_torch *t, t_game *g)
{
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
	if (t->is_opening)
	{
		t->open_frame++;
		if (t->open_frame >= 12)
		{
			t->is_opening = 0;
			t->open_frame = 0;
		}
		return ;
	}
	continue_torch_anim(t, g);
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
		if (t->screen_x >= 0 && t->screen_x < g->screen_width
			&& t->screen_y >= 0 && t->screen_y < g->screen_height)
		{
			pixel = (t->r << 24) | (t->g << 16) | (t->b << 8) | t->alpha;
			mlx_put_pixel(g->img, t->screen_x, t->screen_y, pixel);
		}
	}
}
