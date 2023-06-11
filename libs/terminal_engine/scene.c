#include "term.h"


t_scene	*make_scene(int rows, int cols)
{
	t_scene *res;
	int i;
	int j;

	i = 0;
	res = malloc(sizeof(t_scene));
	res->x = cols;
	res->y = rows;
	res->image = malloc (sizeof(char *) * (rows + 1));
	while (i < rows)
	{
		res->image[i] = malloc(sizeof(char) * (cols + 1));
		res->image[i][0] = '|';
		j = 1;
		while(j < cols - 1)
		{
			res->image[i][j] = ' ';
			j++;
		}
		res->image[i][cols - 1] = '|';
		res->image[i][cols] = '\0';
		i++;
	}
	i = 0;
	while (i < cols)
	{
		res->image[0][i] = '-';
		res->image[rows - 1][i] = '-';
		i++;
	}
	res->image[rows] = NULL;
	return (res);
}

void	draw_scene(t_scene *scene)
{
	int i;

	i = 0;
	while (scene->image[i])
	{
		printf("%s\n", scene->image[i]);
		i++;
	}
}

t_scene	*copy_scene(t_scene *scene)
{
	t_scene	*res;
	int rows = scene->y;
	int cols = scene->x;
	int i;
	int j;

	res = malloc(sizeof(t_scene));
	res->x = cols;
	res->y = rows;
	res->image = malloc(sizeof(char *) * (rows + 1));
	bzero(res->image, sizeof(char *) * (rows + 1));
	i = 0;
	while (i < rows)
	{
		res->image[i] = malloc (sizeof(char) * (cols + 1));
		j = 0;
		while (j < cols)
		{
			res->image[i][j] = scene->image[i][j];
			j++;
		}
		res->image[i][j] = '\0';
		i++;
	}
	res->image[i] = NULL;
	return (res);
}

void	add_object_to_scene(t_object *object, t_scene *scene)
{
	int	x;
	int y;

	y = object->y;

	while (object->image[y - object->y])
	{
		x = object->x;
		while (object->image[y - object->y][x - object->x])
		{
			if (x > 0 && y > 0 && x < scene->x && y < scene->y &&
					object->image[y - object->y][x - object->x] != ' ')
			scene->image[y][x] = object->image[y - object->y][x - object->x];
			x++;
		}
		y++;
	}
}

void	remove_object_from_scene(t_object *object, t_scene *scene, t_scene *original_scene)
{
	int	x;
	int y;

	y = object->y;

	while (object->image[y - object->y])
	{
		x = object->x;
		while (object->image[y - object->y][x - object->x])
		{
			if (x > 0 && y > 0 && x < scene->x && y < scene->y)
			scene->image[y][x] = original_scene->image[y][x];
			x++;
		}
		y++;
	}
}
void	free_scene(t_scene *scene)
{
	int	i;

	i = 0;
	while(scene->image[i])
	{
		free(scene->image[i]);
		i++;
	}
	free(scene->image);
	free(scene);
}

int	resize(t_settings_term *settings)
{
	int	*mid_value;
	mid_value = get_screen_size();
	if (!equal_size(settings->scene_size, mid_value))
	{
		free(settings->scene_size);
		settings->scene_size = mid_value;
		free_scene(settings->initial_scene);
		free_scene(settings->actual_scene);
		settings->initial_scene = make_scene(mid_value[0] - 1, mid_value[1] - 1);
		settings->actual_scene = copy_scene(settings->initial_scene);
		return (1);
	}
	free(mid_value);
	return (0);
}