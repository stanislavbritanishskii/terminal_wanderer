/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhendzel <dhendzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 18:54:31 by sbritani          #+#    #+#             */
/*   Updated: 2023/04/10 02:48:41 by dhendzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	ft_hook(void *param)
{

	t_settings		*settings;
	int				key;

	int sleep_interval = 20000;
	settings = param;

	while (1)
	{

		if (resize(settings->term))
			printf("resized\n");
		key = get_pressed(settings->term);
//		add_fps_to_scene(settings->term->)
		if (key == 27)
		{
			clean_settings(settings);
			exit (0);
		}
		if (key == (int)'d') {
			move_character(settings, RIGHT);
		}
		if (key == 'a') {
			move_character(settings, LEFT);
		}
		if (key == (int)'w') {
			move_character(settings, FORWARD);
		}
		if (key == 's') {
			move_character(settings, BACKWARD);
		}
		if (key =='e') {
			rotate_point(settings, TURN_ANGLE);
		}
		if (key == 'q') {
			rotate_point(settings, -TURN_ANGLE);
		}
		if (key == 'z') {
			reset_view(settings);
		}
		if (key == 'p')
			sleep_interval += 1000;
		if (key == 'o')
			sleep_interval -= 1000 * (sleep_interval > 0);

		draw_sky_floor(settings);
		draw_walls(settings);
//		for (int i =0; i < settings->term->actual_scene->x * settings->term->actual_scene->y - 100; i ++) {
////			printf ("%d", i);
//			if (settings->term->actual_scene->image[i / settings->term->actual_scene->x][i %
//																						 settings->term->actual_scene->x] !=
//				' ')
//				printf("%c\n", settings->term->actual_scene->image[i / settings->term->actual_scene->x][i %settings->term->actual_scene->x]);
////			printf("\n");
//		}
		add_fps_to_scene(get_fps(), settings->term->actual_scene);
		draw_scene(settings->term->actual_scene);
//		print_map(settings->map, settings->observer_position, settings->point_of_view);
//		printf("%d %f \n", key, settings->observer_position->x);
		usleep(sleep_interval);
	}
}

int	main(int argc, char **argv)
{
	t_settings	*settings;

	settings = NULL;
	if (argc == 2)
		settings = init_settings(argv[1]);
	else
		ft_putstr_fd("Error\nWrong input\n", 2);
	change_raw();
	change_echo();
	resize(settings->term);
	run_pressed_thread(settings->term);
	if (settings)
	{
//		draw_sky_floor(settings);
		ft_hook(settings);
//		mlx_loop_hook(settings->mlx, ft_hook, settings);
//		mlx_loop(settings->mlx);
		clean_settings(settings);
		return (0);
	}
	return (1);
}
