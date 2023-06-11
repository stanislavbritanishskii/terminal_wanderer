#include "term.h"

void	fill_map_with_dots(t_scene *scene, int n)
{
    int	i;
    int	j;

    i = 1;
    while (scene->image[i])
    {
        j = 1;
        while (scene->image[i][j])
        {
            if ((i + j) % n == 0 && i != scene->y - 1 && j != scene->x - 1)
                scene->image[i][j] = '.';
            j++;
        }
        i++;
    }
}

int	get_fps()
{
    static int prev_time = 0;
    static int prev_fps = 0;
    static int current_fps = 0;

    if (get_other_time() / 1000 != prev_time)
    {
        prev_time = get_other_time() / 1000;
        prev_fps = current_fps;
        current_fps = 0;
    }
    current_fps++;
    return (prev_fps);
}

//void	add_fps_to_scene(t_fps *fps, t_scene *scene)
//{
//    int i;
//
//    i = 0;
//    while (fps->fps_str[i] && scene->image[0][i])
//    {
//        scene->image[0][i] = fps->fps_str[i];
//        i++;
//    }
//}

void	add_fps_to_scene(int fps, t_scene *scene)
{
	int i;
	char *fps_str;

	fps_str = ft_itoa(fps);
	fps_str = ft_str_join_free_first_term(fps_str, " FPS");
	i = 0;
	while (fps_str[i] && scene->image[0][i])
	{
		scene->image[0][i] = fps_str[i];
		i++;
	}
}