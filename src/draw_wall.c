/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhendzel <dhendzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 22:29:53 by dhendzel          #+#    #+#             */
/*   Updated: 2023/04/10 02:44:11 by dhendzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	put_pixel(t_settings *settings, int x, int y, uint32_t color)
{
//	mlx_put_pixel(settings->image, x, y, color);
//	printf("%d %d %d %d \n", x, y, settings->term->scene_size[0], settings->term->scene_size[1]);
//	printf("%s\n", settings->term->actual_scene->image[y]);
//	printf("%zu\n", ft_strlen(settings->term->actual_scene->image[y]));
	if (x < 0 || x > settings->term->scene_size[1] - 1 || y < 0 || y > settings->term->scene_size[0] - 1)
		return ;
    if (color == 1)
        settings->term->actual_scene->image[y][x] = '@';
    else if (color == 0)
        settings->term->actual_scene->image[y][x] = ' ';
	else if (color == 2)
		settings->term->actual_scene->image[y][x] = 'O';
}

void	draw_line_floor_sky(t_settings *settings, int x)
{
	int		i;
//	int		color;
//	float	darkness;

	i = 0;
	while (i < settings->term->scene_size[0] / 2)
	{
//		darkness = 1 - (((float)RANDOM / ((float)settings->term->scene_size[1] / 2 - i))
//				/ (float) settings->max_distance);
//		if (darkness < 0) {
//			darkness = 0;
//		}
//		color = get_color(settings->ceiling_color, darkness);
		put_pixel(settings, x, i, 0);

		i++;
	}
	while (i < settings->term->scene_size[0] - 1)
	{
//		darkness = 1 - (((float)RANDOM / ((float)i
//						- (float)settings->term->scene_size[1] / 2)) / (float) settings->max_distance);
//		if (darkness < 0)
//			darkness = 0;
//		color = get_color(settings->floor_color, darkness);
		put_pixel(settings, x, i, 0);
		i++;
	}
}

void	draw_direction(t_settings *settings, t_march_return *march, float d)
{
	t_texture	texture;

	texture.height = settings->term->scene_size[0] / (march->distance + SMALL) / 2;
	texture.x_shift = march->shift;
	texture.d = d;
//	if (march->direction == SO)
	draw_texture_line(settings,  &texture);
//	if (march->direction == EA)
//		draw_texture_line(settings,  &texture);
//	if (march->direction == NO)
//		draw_texture_line(settings,  &texture);
//	if (march->direction == WE)
//		draw_texture_line(settings,  &texture);
//	if (march->direction == 5)
//		draw_line_floor_sky(settings, d);
}

void	draw_walls(t_settings *settings)
{
	float			d;
	float			angle;
	t_vector		direction;
	t_march_return	march;

	d = settings->term->scene_size[1] - 2;
	angle = -0.15f * M_PI;
	while (d >= 0)
	{
		direction = get_ray_direction(*settings->observer_position,
				*settings->point_of_view, angle);
		ray_march(settings,
			direction, settings->map, &march);
		march.distance *= cosf(angle);
		draw_direction(settings, &march, d);
//		printf("here\n");
		d = d - 1;
		angle += 0.3f * M_PI / (settings->term->scene_size[1] - 1);
//		printf("%f\n", angle);
	}
//	exit (1);
}

void	draw_sky_floor(t_settings *settings)
{
	float		d;

	d = settings->term->scene_size[1] - 2;
	while (d >= 0)
	{
		draw_line_floor_sky(settings, d);
		d--;
	}
}
