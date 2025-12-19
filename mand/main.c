#include "cube.h"

void loop_hook(void *param)
{
    t_game *g = param;

    handle_movement(g);
    memset(g->img->pixels, 0, g->screen_width * g->screen_height* 4);
    cast_rays(g);
    draw_minimap(g);
    draw_torch_sprite(g);
}

void lll()
{
	system("leaks Cube3d");
}
void dynamic_resizing(int width,int height,void *param)
{
	t_game *g;
	g = (t_game *) param;
	mlx_delete_image(g->mlx, g->img);
	g->img = mlx_new_image(g->mlx,width,height);
	if(!g->img)
		return;
	g->screen_height = height;
	g->screen_width = width;
	cast_rays(g);
    draw_minimap(g);
    draw_torch_sprite(g);
	mlx_image_to_window(g->mlx,g->img,0,0);
}
int main(int argc, char **argv)
{
	atexit(lll);
    t_game g;

    g.screen_width = 800;
    g.screen_height = 600;
    g.my_map = map_fill(argc, argv);
    if (g.my_map == NULL)
        return 1;
    get_map_dimensions(&g);
    init_player(&g.player, &g);
    if (fill_textur(g.my_map, &g) == 1)
        return 1;
    g.img = mlx_new_image(g.mlx, g.screen_width, g.screen_height);
    mlx_image_to_window(g.mlx, g.img, 0, 0);
	mlx_resize_hook(g.mlx,&dynamic_resizing,&g);
    mlx_set_cursor_mode(g.mlx, MLX_MOUSE_HIDDEN); 
    mlx_loop_hook(g.mlx, loop_hook, &g);
    mlx_loop(g.mlx);
    free_mymap(g.my_map);
    free_texturs(&g);
    return (0);
}
