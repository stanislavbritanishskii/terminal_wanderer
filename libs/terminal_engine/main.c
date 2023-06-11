#include "term.h"


// void	check_leaks()
// {
// 	system("leaks a.out");
// }

t_object *make_stone()
{
	t_object *res;

	res = create_object("objects/ball.txt");
	res->total_clicks_till_move = 1;
	res->clicks_till_move = 10;
	res->x = 30;
	res->y = 30;
	res->x_dir = 3;
	res->y_dir = 1;
	return (res);
}

void	bouncy_move(t_object *object, t_settings *settings)
{
	t_scene *scene = settings->actual_scene;
	if (!object->clicks_till_move)
	{
		remove_object_from_scene(object, scene, settings->initial_scene);
		object->x += object->x_dir;
		if (object->x + object->x_size >= scene->x)
		{
			object->x_dir *=-1;
			object->x = scene->x - object->x_size - 1;
		}
		if (object->x<= 0)
		{
			object->x_dir *=-1;
			object->x = 1;
		}
		object->y += object->y_dir;
		if (object->y + object->y_size >= scene->y)
		{
			object->y_dir *=-1;
			object->y = scene->y - object->y_size - 1;
		}
		if (object->y <= 0)
		{
			object->y_dir *=-1;
			object->y = 1;
		}
		add_object_to_scene(object, scene);
		object->clicks_till_move = object->total_clicks_till_move;
	}
	add_object_to_scene(object, scene);
	object->clicks_till_move--;
}

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







int main (int argc, char **argv)
{
	int	*mid_value;
	int c = 0;
	t_settings *settings;
	t_object *object;
	t_object *ball, *ball1, *ball2, *ball3;
	t_fps *fps;
	char **scene;
	int sleep_time;

	settings = init_settings();
	sleep_time = 10000;
	fps = malloc(sizeof(t_fps));
	fps->fps = get_fps();
	fps->fps_str = ft_itoa(fps->fps);
	object = create_object("objects/object.txt");
	ball = make_stone();
	ball1 = make_stone();
	ball1->x_dir = 20;
	ball2 = make_stone();
	ball2->y_dir *= -3;
	ball3 = make_stone();
	ball3->y_dir -= 2;
	ball3->x_dir -= 4;
	change_echo();
	change_raw();
	// atexit(check_leaks);
	run_pressed_thread(settings);
	fill_map_with_dots(settings->initial_scene, 3);
	free_scene(settings->actual_scene);
	settings->actual_scene = copy_scene(settings->initial_scene);
	while (c != '!')
	{
		c = get_pressed(settings);
		if (resize(settings))
		{
			fill_map_with_dots(settings->initial_scene, 3);
			free_scene(settings->actual_scene);
			settings->actual_scene = copy_scene(settings->initial_scene);
		}
		if (get_fps() != fps->fps)
		{
//			fps->fps = get_fps();
//			free(fps->fps_str);
//			fps->fps_str =ft_str_join_free_first(ft_itoa(fps->fps), " FPS");
			add_fps_to_scene(fps->fps, settings->actual_scene);
		}
		remove_object_from_scene(object, settings->actual_scene, settings->initial_scene);
		if (c == 'w')
			object->y--;
		if (c == 's')
			object->y++;
		if (c == 'a')
			object->x -= 2;
		if (c == 'd')
			object->x += 2;
		if (c == '+')
			sleep_time += 200;
		if (c == '-')
			sleep_time -= 200;
		if (sleep_time < 0)
			sleep_time = 0;
		bouncy_move(ball, settings);
		bouncy_move(ball1, settings);
		bouncy_move(ball2, settings);
		bouncy_move(ball3, settings);
		add_object_to_scene(object, settings->actual_scene);
		draw_scene(settings->actual_scene);
		usleep(sleep_time);
	}
	free_object(object);
	free(fps->fps_str);
	free(fps);
	free_object(ball);
	free_object(ball1);
	free_object(ball2);
	free_object(ball3);
	clear_settings(settings);
	printf("\n");
	change_raw();
	change_echo();
}