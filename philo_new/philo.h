/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 00:17:13 by jaemjeon          #+#    #+#             */
/*   Updated: 2022/07/13 19:01:45 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

# define INT_MAX 2147483647
# define ERROR -1
# define DEAD 1
# define UNLOCK 0
# define LOCK 1
# define TRUE 1
# define FALSE 0

typedef struct s_union
{
	pthread_t		*philo_thread;
	pthread_mutex_t	*fork_key;
	pthread_mutex_t	start_line;
	pthread_mutex_t	voice;
	int				*fork_status;
	long			time_to_died;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_to_each_must_eat;
	long			time_to_start;
	long			num_of_philo;
	int				is_someone_dead;
	int				all_philo_full;
}	t_union;

typedef struct s_philo
{
	t_union 	*info_union;
	long		time_last_meal;
	int			eat_count;
	int			my_right_fork_id;
	int			my_left_fork_id;
	int			my_id;
}	t_philo;

// main.c
void	ft_print_log(t_philo *info_philo, long time, \
						char *message, int is_last);

// init.c
int	malloc_in_union_resources(t_union *info_union);
void	free_memory_in_union(t_union *info_union);
void	link_all_philo_to_union(t_philo *info_philo_arr, t_union *info_union);

// parsing.c
int	parsing(t_union *info_union, int argc, char **argv);

// util.c
long	ft_atol(char *str);
int	ft_error(void);
long	get_cur_time(void);
long	ft_time_diff(long time1, long time2);
void	init_mutex_and_make_philos(t_philo *info_philo_arr);

// philo.c
void	*philo_even(void *info_philo);
void	*philo_odd(void *info_philo);

// philo_behave.c
void	get_my_rigth_fork(t_philo *info_philo);
void	get_my_left_fork(t_philo *info_philo);
void	philo_eat(t_philo *info_philo);
void	philo_sleep(t_philo *info_philo);
void	philo_think(t_philo *info_philo);
#endif
