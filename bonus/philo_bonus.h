/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:41:55 by jaemjeon          #+#    #+#             */
/*   Updated: 2022/07/28 19:12:00 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <string.h>

# define TRUE 1
# define FALSE 0
# define ERROR -1
# define INT_MAX 2147483647
# define LOCK 1
# define UNLOCK 0
# define NONE 0
# define LASTSPEAK 1
# define DEAD 1
# define FULL 2
# define LLONG_MAX 9223372036854775807

typedef struct s_union
{
	int				stop_eating;
	size_t			num_of_philo;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			time_to_start;
	size_t			num_each_philo_must_eat;
	sem_t			*forks_set;
	sem_t			*voice;
	sem_t			*start_key;
	pid_t			*philo_pid_arr;
}	t_union;

typedef struct s_philo
{
	size_t			my_id;
	size_t			time_of_last_meal;
	int				eat_count;
	pthread_mutex_t	mutex_time_of_last_meal;
	t_union			*info_union;
}	t_philo;

// main_bonus.c

//parsing_bonus.c
void	parsing(t_union *info_union, int argc, char **argv);

//philo_behave_bonus.c
void	philo_is_speaking(t_philo *info_philo, char *message);
void	pick_up_forks(t_philo *info_philo);
void	philo_eat(t_philo *info_philo);
void	philo_sleep(t_philo *info_philo);
void	philo_think(t_philo *info_philo);

//util_bonus.c
size_t	ft_atoul_check_range(char *str);
void	ft_error(t_union *info_union);
size_t	get_cur_time(void);
size_t	get_time_stamp(t_union *info_union);

//util2_bonus.c
int		paras_is_in_valid_range(t_union *info_union, int argc);
void	*ft_calloc(size_t size);

//philo_bonus.c
void	philo_process(t_philo *info_philo);

#endif
