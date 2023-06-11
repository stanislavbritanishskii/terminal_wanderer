#include "term.h"

t_settings_term *init_settings_term(void)
{
    t_settings_term *res;

    res = malloc(sizeof(t_settings_term));
    res->pressed = malloc(sizeof(int));
    res->pressed[0] = 0;
    res->pressed_lock = malloc(sizeof(pthread_mutex_t));
    res->scene_size = get_screen_size();
    res->initial_scene = make_scene(res->scene_size[0] - 1, res->scene_size[1] - 1);
    res->actual_scene = copy_scene(res->initial_scene);
    pthread_mutex_init(res->pressed_lock, NULL);
    res->value = 0;
    res->pressed_thread = create_thread();
    return (res);
}

void	clear_settings(t_settings_term *settings)
{
    pthread_mutex_lock(settings->pressed_lock);
    settings->pressed[0] = -1;
    pthread_mutex_unlock(settings->pressed_lock);
    pthread_join(*settings->pressed_thread, NULL);
    free(settings->pressed);
    pthread_mutex_destroy(settings->pressed_lock);
    free(settings->pressed_lock);
    free(settings->pressed_thread);
    free(settings->scene_size);
    free_scene(settings->initial_scene);
    free_scene(settings->actual_scene);
    free(settings);
}