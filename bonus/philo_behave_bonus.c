/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behave_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 00:38:05 by jaemjeon          #+#    #+#             */
/*   Updated: 2022/07/23 01:52:02 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_is_speaking(t_philo *info_philo, char *message, int flag)
{
	size_t	time_stamp;

	sem_wait(info_philo->info_union->voice);
	if (info_philo->info_union->stop_eating == TRUE)
		return ;
	if (flag == LASTSPEAK)
		info_philo->info_union->stop_eating = TRUE;
	time_stamp = get_cur_time() - info_philo->info_union->time_to_start;
	printf("%zu %zu %s\n", time_stamp, info_philo->my_id, message);
	sem_post(info_philo->info_union->voice);
}

void	pick_up_forks(t_philo *info_philo)
{
	check_is_dead(info_philo);
	sem_wait(info_philo->info_union->forks);
	philo_is_speaking(info_philo, "has taken a fork", NONE);
	sem_wait(info_philo->info_union->forks);
	philo_is_speaking(info_philo, "has taken a fork", NONE);
}

void	philo_eat(t_philo *info_philo)
{
	size_t	time_to_finish_eat;

	check_is_dead(info_philo);
	time_to_finish_eat = get_cur_time() + info_philo->info_union->time_to_eat;
	philo_is_speaking(info_philo, "is eating", NONE);
	while (get_cur_time() < time_to_finish_eat)
		usleep(300);
	info_philo->eat_count++;
	if (info_philo->eat_count == \
							info_philo->info_union->num_each_philo_must_eat)
		sem_wait(info_philo->info_union->full_count);
	sem_post(info_philo->info_union->forks);
	sem_post(info_philo->info_union->forks);
}

void	philo_sleep(t_philo *info_philo)
{
	size_t	time_to_wake;

	check_is_dead(info_philo);
	time_to_wake = get_cur_time() + info_philo->info_union->time_to_sleep;
	philo_is_speaking(info_philo, "is sleeping", NONE);
	while (get_cur_time() < time_to_wake)
		usleep(300);
}

void	philo_think(t_philo *info_philo)
{
	check_is_dead(info_philo);
	philo_is_speaking(info_philo, "is thinking", NONE);
}
