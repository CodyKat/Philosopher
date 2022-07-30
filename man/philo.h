/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:41:55 by jaemjeon          #+#    #+#             */
/*   Updated: 2022/07/30 18:06:02 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>

# define TRUE 1
# define FALSE 0
# define ERROR -1
# define INT_MAX 2147483647
# define LOCK 1
# define UNLOCK 0
# define NONE 0
# define LASTSPEAK 1

typedef struct s_union
{
	int				stop_eating;
	size_t			num_of_philo;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			time_to_start;
	size_t			num_each_philo_must_eat;
	int				*fork_status;
	pthread_t		**philo_arr;
	pthread_mutex_t	**fork_arr;
	pthread_mutex_t	voice;
	pthread_mutex_t	start_key;
}	t_union;

typedef struct s_philo
{
	size_t			my_id;
	size_t			time_of_last_meal;
	int				right_fork_id;
	int				left_fork_id;
	int				eat_count;
	t_union			*info_union;
}	t_philo;

//main.c
int		check_is_someone_dead(t_philo *info_philo_arr);
int		check_all_philo_is_full(t_philo *info_philo_arr);

//parsing.c
int		parsing(t_union *info_union, int argc, char **argv);

//util.c
int		ft_error(void);
size_t	ft_atoul_check_range(char *str);
size_t	get_cur_time(void);

//util2.c
int		paras_is_in_valid_range(t_union *info_union, int argc);
void	*ft_calloc(size_t size);

//init.c
int		malloc_all_resources(t_union *info_union, t_philo **info_philo_arr, \
																int n_philo);
int		malloc_and_init_resources(t_union *info_union, \
													t_philo **info_philo_arr);
void	free_all_resources(t_union *info_union, t_philo **info_philo_arr);
void	init_all_resources(t_union *info_union, t_philo *info_philo_arr);

//philo_func.c
void	*philo_even(void *info_philo);
void	*philo_odd(void *info_philo);

//philo_behave.c
void	philo_is_speaking(t_philo *philo_info, size_t philo_id, char *message);
void	get_my_left_fork(t_philo *my_info);
void	get_my_right_fork(t_philo *my_info);
void	philo_eat(t_philo *my_info);
void	philo_sleep(t_philo *my_info);

//philo_thinking.c
void	philo_think(t_philo *my_info);

//watcher_func.c
void	watcher_no_optional(t_philo *info_philo_arr);
void	watcher_optional(t_philo *info_philo_arr);

#endif
