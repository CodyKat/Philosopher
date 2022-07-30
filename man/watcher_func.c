/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 17:57:30 by jaemjeon          #+#    #+#             */
/*   Updated: 2022/07/30 18:03:17 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	watcher_no_optional(t_philo *info_philo_arr)
{
	int		n_philo;
	int		num_of_philo;
	int		each_philo_must_eat;
	size_t	time_to_die;

	num_of_philo = info_philo_arr->info_union->num_of_philo;
	each_philo_must_eat = info_philo_arr->info_union->num_each_philo_must_eat;
	time_to_die = info_philo_arr->info_union->time_to_die;
	while (check_is_someone_dead(info_philo_arr) == FALSE)
	{
	}
	info_philo_arr->info_union->stop_eating = TRUE;
	pthread_mutex_unlock(&info_philo_arr->info_union->voice);
	n_philo = -1;
	while (++n_philo < info_philo_arr->info_union->num_of_philo)
		pthread_join(*info_philo_arr->info_union->philo_arr[n_philo], NULL);
}

void	watcher_optional(t_philo *info_philo_arr)
{
	int		n_philo;
	int		num_of_philo;
	int		each_philo_must_eat;
	size_t	time_to_die;

	num_of_philo = info_philo_arr->info_union->num_of_philo;
	each_philo_must_eat = info_philo_arr->info_union->num_each_philo_must_eat;
	time_to_die = info_philo_arr->info_union->time_to_die;
	while (check_is_someone_dead(info_philo_arr) == FALSE \
			&& check_all_philo_is_full(info_philo_arr) == FALSE)
	{
	}
	info_philo_arr->info_union->stop_eating = TRUE;
	pthread_mutex_unlock(&info_philo_arr->info_union->voice);
	n_philo = -1;
	while (++n_philo < info_philo_arr->info_union->num_of_philo)
		pthread_join(*info_philo_arr->info_union->philo_arr[n_philo], NULL);
}
