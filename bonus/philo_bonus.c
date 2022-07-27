/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 23:37:50 by jaemjeon          #+#    #+#             */
/*   Updated: 2022/07/27 22:34:20 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_loop(t_philo *info_philo)
{
	if (info_philo->my_id % 2 == 1)
		usleep(1000);
	while (1)
	{
		pick_up_forks(info_philo);
		philo_eat(info_philo);
		philo_sleep(info_philo);
		philo_think(info_philo);
		if (info_philo->my_id % 2 == 1)
			usleep(300);
	}
}

void	*philo_check_dead_loop(void *info_parameter)
{
	t_philo	*info_philo;

	info_philo = (t_philo *)info_parameter;
	while (1)
	{
		pthread_mutex_lock(&info_philo->mutex_time_of_last_meal);
		if (info_philo->info_union->time_to_die <= \
				get_cur_time() - info_philo->time_of_last_meal)
		{
			sem_wait(info_philo->info_union->dead);
			printf("%zu %zu died\n", \
					get_time_stamp(info_philo->info_union), info_philo->my_id);
			exit(DEAD);
		}
		pthread_mutex_unlock(&info_philo->mutex_time_of_last_meal);
		usleep(1000);
	}
}

void	philo_process(t_philo *info_philo)
{
	pthread_t	philo_thread;

	info_philo->time_of_last_meal = info_philo->info_union->time_to_start;
	sem_wait(info_philo->info_union->start_key);
	sem_post(info_philo->info_union->start_key);
	pthread_mutex_init(&info_philo->mutex_time_of_last_meal, NULL);
	pthread_create(&philo_thread, NULL, philo_check_dead_loop, info_philo);
	pthread_detach(philo_thread);
	philo_loop(info_philo);
}
