/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 19:22:55 by jaemjeon          #+#    #+#             */
/*   Updated: 2022/07/30 20:59:59 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_eat_with_no_option(t_philo *info_philo)
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
	sem_post(info_philo->info_union->forks_set);
}

void	philo_eat_with_option(t_philo *info_philo)
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
	sem_post(info_philo->info_union->forks_set);
	info_philo->eat_count++;
	if (info_philo->eat_count == \
						(int)info_philo->info_union->num_each_philo_must_eat)
	{
		philo_is_speaking(info_philo, "is full");
		exit(FULL);
	}
}
