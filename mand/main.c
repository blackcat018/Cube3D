#include "cube.h"

//add this shit to the bonus part you idiot!

//seriously how did you survive this far!?
void loop_hook(void *param)
{
    t_game *g = param;

    handle_movement(g);
    memset(g->img->pixels, 0, SCREEN_WIDTH * SCREEN_HEIGHT * 4);
    cast_rays(g);
    draw_minimap(g);
    draw_torch_sprite(g);
}

void lll()
{
	system ("leaks Cube3d");
}

int main(int argc, char **argv)
{
    t_game g;
    
    g.my_map = map_fill(argc, argv);
    if (g.my_map == NULL)
        return 1;
    
    get_map_dimensions(&g);
    init_player(&g.player, &g);
    
    if (fill_textur(g.my_map, &g) == 1)
        return 1;
    
    g.img = mlx_new_image(g.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    mlx_image_to_window(g.mlx, g.img, 0, 0);
    
    mlx_set_cursor_mode(g.mlx, MLX_MOUSE_HIDDEN);
    
    atexit(lll);
    mlx_loop_hook(g.mlx, loop_hook, &g);
    mlx_loop(g.mlx);
    
    free_mymap(g.my_map);
    free_texturs(&g);
    return (0);
}
