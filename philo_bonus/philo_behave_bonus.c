/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behave_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 00:38:05 by jaemjeon          #+#    #+#             */
/*   Updated: 2022/08/11 19:42:38 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_is_speaking(t_philo *info_philo, size_t time_stamp, char *message)
{
	sem_wait(info_philo->info_union->voice);
	printf("%zu %zu %s\n", time_stamp, info_philo->my_id, message);
	sem_post(info_philo->info_union->voice);
}

void	pick_up_forks(t_philo *info_philo)
{
	sem_wait(info_philo->info_union->sem_get_forks);
	sem_wait(info_philo->info_union->forks_set);
	philo_is_speaking(info_philo, get_time_stamp(info_philo->info_union), \
															"has taken a fork");
	sem_wait(info_philo->info_union->forks_set);
	philo_is_speaking(info_philo, get_time_stamp(info_philo->info_union), \
															"has taken a fork");
	sem_post(info_philo->info_union->sem_get_forks);
}

void	philo_sleep(t_philo *info_philo)
{
	size_t	time_to_wake;

	time_to_wake = get_cur_time() + info_philo->info_union->time_to_sleep;
	philo_is_speaking(info_philo, get_time_stamp(info_philo->info_union), \
																"is sleeping");
	while (get_cur_time() < time_to_wake)
		usleep(300);
}

void	philo_think(t_philo *info_philo)
{
	philo_is_speaking(info_philo, get_time_stamp(info_philo->info_union), \
																"is thinking");
}
