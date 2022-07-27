/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behave_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 00:38:05 by jaemjeon          #+#    #+#             */
/*   Updated: 2022/07/27 17:39:44 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_is_speaking(t_philo *info_philo, char *message)
{
	sem_wait(info_philo->info_union->voice);
	sem_wait(info_philo->info_union->dead);
	sem_post(info_philo->info_union->dead);
	printf("%zu %zu %s\n", \
				get_time_stamp(info_philo), info_philo->my_id, message);
	sem_post(info_philo->info_union->voice);
}

void	pick_up_forks(t_philo *info_philo)
{
	sem_wait(info_philo->info_union->forks_set);
	philo_is_speaking(info_philo, "has taken a fork");
	philo_is_speaking(info_philo, "has taken a fork");
}

void	philo_eat(t_philo *info_philo)
{
	size_t	time_to_finish_eat;

	pthread_mutex_lock(&info_philo->mutex_time_of_last_meal);
	info_philo->time_of_last_meal = get_cur_time();
	pthread_mutex_unlock(&info_philo->mutex_time_of_last_meal);
	time_to_finish_eat = \
			info_philo->time_of_last_meal + info_philo->info_union->time_to_eat;
	philo_is_speaking(info_philo, "is eating");
	while (get_cur_time() < time_to_finish_eat)
		usleep(300);
	info_philo->eat_count++;
	sem_post(info_philo->info_union->forks_set);
	if (info_philo->eat_count == \
							info_philo->info_union->num_each_philo_must_eat)
		exit(FULL);
}

void	philo_sleep(t_philo *info_philo)
{
	size_t	time_to_wake;

	time_to_wake = get_cur_time() + info_philo->info_union->time_to_sleep;
	philo_is_speaking(info_philo, "is sleeping");
	while (get_cur_time() < time_to_wake)
		usleep(300);
}

void	philo_think(t_philo *info_philo)
{
	philo_is_speaking(info_philo, "is thinking");
}
