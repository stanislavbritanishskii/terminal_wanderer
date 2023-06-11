#ifndef TERM_H
# define TERM_H
#include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <stdio.h>
# include <unistd.h>
# include "get_next_line_bonus.h"
# include <fcntl.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_object
{
	char **image;
	int	clicks_till_move;
	int	total_clicks_till_move;
	int	x;
	int	y;
	int x_size;
	int y_size;
	int x_dir;
	int y_dir;
}				t_object;

typedef struct s_fps
{
	int fps;
	char *fps_str;
	int x;
	int y;
}				t_fps;

typedef struct s_scene
{
	char **image;
	int	x;
	int	y;
}				t_scene;

typedef struct s_settings_term
{
	pthread_mutex_t *pressed_lock;
	t_scene	*initial_scene;
	t_scene	*actual_scene;
	int		*scene_size;
	int	*pressed;
	pthread_t	*pressed_thread;
	int	value;
}				t_settings_term;

//terminal input state changes
void	change_echo(void);
void	change_raw(void);
//

//pressed process
void	*thread(void	*input);
int	get_pressed(t_settings_term *settings);
pthread_t	*create_thread(void);
void	run_pressed_thread(t_settings_term *settings);

// scene functions
t_scene	*make_scene(int rows, int cols);
void	draw_scene(t_scene *scene);
t_scene	*copy_scene(t_scene *scene);
void	add_object_to_scene(t_object *object, t_scene *scene);
void	remove_object_from_scene(t_object *object, t_scene *scene, t_scene *original_scene);
void	free_scene(t_scene *scene);
int	resize(t_settings_term *settings);

// object functions
t_object *create_object(char *path);
char **read_image(char *path);
void free_object(t_object *object);

// utils
char	**add_string_to_string_arr_term(char *str, char **arr, int n);
char *str_copy_term(char *str, int n);
int	*get_screen_size();
int equal_size(int *s1, int *s2);
long long	get_time(void);
int	get_other_time(void);
int	get_fps();
void	add_fps_to_scene(int fps, t_scene *scene);

//
char	*ft_itoa(int n);
char	*ft_str_join_free_first_term(char *str1, char *str2);

//
//void	add_fps_to_scene(t_fps *fps, t_scene *scene);
int	get_fps();
void	fill_map_with_dots(t_scene *scene, int n);
//
t_settings_term *init_settings_term(void);
void	clear_settings(t_settings_term *settings);

#endif