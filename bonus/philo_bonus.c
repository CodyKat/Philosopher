/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 23:37:50 by jaemjeon          #+#    #+#             */
/*   Updated: 2022/08/03 16:19:10 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_odd_loop(t_philo *info_philo)
{
	void	(*philo_eat)(t_philo *);

	if (info_philo->info_union->has_optional_arg == TRUE)
		philo_eat = philo_eat_with_option;
	else
		philo_eat = philo_eat_with_no_option;
	usleep(1000);
	while (1)
	{
		pick_up_forks(info_philo);
		philo_eat(info_philo);
		philo_sleep(info_philo);
		philo_think(info_philo);
		usleep(300);
	}
}

void	philo_even_loop(t_philo *info_philo)
{
	void	(*philo_eat)(t_philo *);

	if (info_philo->info_union->has_optional_arg == TRUE)
		philo_eat = philo_eat_with_option;
	else
		philo_eat = philo_eat_with_no_option;
	while (1)
	{
		pick_up_forks(info_philo);
		philo_eat(info_philo);
		philo_sleep(info_philo);
		philo_think(info_philo);
	}
}

void	*philo_check_dead_loop(void *info_parameter)
{
	t_philo	*info_philo;
	t_union	*info_union;
	size_t	philo_id;

	info_philo = (t_philo *)info_parameter;
	info_union = info_philo->info_union;
	philo_id = info_philo->my_id;
	while (1)
	{
		pthread_mutex_lock(&info_philo->mutex_time_of_last_meal);
		if (is_dead(info_philo))
		{
			sem_wait(info_philo->info_union->voice);
			printf("%zu %zu died\n", get_time_stamp(info_union), philo_id);
			exit(DEAD);
		}
		pthread_mutex_unlock(&info_philo->mutex_time_of_last_meal);
		usleep(1000);
	}
}

void	philo_process(t_philo *info_philo)
{
	pthread_t	philo_thread;
	void		(*my_loop)(t_philo *);

	if (info_philo->my_id % 2 == 0)
		my_loop = philo_even_loop;
	else
		my_loop = philo_odd_loop;
	sem_wait(info_philo->info_union->start_key);
	sem_post(info_philo->info_union->start_key);
	pthread_mutex_init(&info_philo->mutex_time_of_last_meal, NULL);
	pthread_create(&philo_thread, NULL, philo_check_dead_loop, info_philo);
	pthread_detach(philo_thread);
	my_loop(info_philo);
}
