/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behave.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 17:48:22 by jaemjeon          #+#    #+#             */
/*   Updated: 2022/08/10 01:20:02 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_is_speaking(t_philo *philo_info, size_t philo_id, char *message)
{
	size_t	time_stamp;

	pthread_mutex_lock(&philo_info->info_union->voice);
	if (philo_info->info_union->stop_eating == TRUE)
	{
		pthread_mutex_unlock(&philo_info->info_union->voice);
		return ;
	}
	time_stamp = get_cur_time() - philo_info->info_union->time_to_start;
	printf("%zu %zu %s\n", time_stamp, philo_id, message);
	pthread_mutex_unlock(&philo_info->info_union->voice);
}

void	get_my_left_fork(t_philo *my_info)
{
	pthread_mutex_lock(my_info->info_union->fork_arr[my_info->left_fork_id]);
	my_info->info_union->fork_status[my_info->left_fork_id] = LOCK;
	philo_is_speaking(my_info, my_info->my_id, "has taken a fork");
}

void	get_my_right_fork(t_philo *my_info)
{
	pthread_mutex_lock(my_info->info_union->fork_arr[my_info->right_fork_id]);
	my_info->info_union->fork_status[my_info->right_fork_id] = LOCK;
	philo_is_speaking(my_info, my_info->my_id, "has taken a fork");
}

void	philo_eat(t_philo *my_info)
{
	size_t	time_to_finish_eat;

	time_to_finish_eat = get_cur_time() + my_info->info_union->time_to_eat;
	pthread_mutex_lock(&my_info->m_time_of_last_meal);
	my_info->time_of_last_meal = get_cur_time();
	pthread_mutex_unlock(&my_info->m_time_of_last_meal);
	philo_is_speaking(my_info, my_info->my_id, "is eating");
	while (get_cur_time() < time_to_finish_eat)
		usleep(300);
	pthread_mutex_lock(&my_info->m_eat_count);
	my_info->eat_count++;
	pthread_mutex_unlock(&my_info->m_eat_count);
	my_info->info_union->fork_status[my_info->left_fork_id] = UNLOCK;
	my_info->info_union->fork_status[my_info->right_fork_id] = UNLOCK;
	pthread_mutex_unlock(my_info->info_union->fork_arr[my_info->left_fork_id]);
	pthread_mutex_unlock(my_info->info_union->fork_arr[my_info->right_fork_id]);
}

void	philo_sleep(t_philo *my_info)
{
	size_t	time_to_wakeup;

	time_to_wakeup = get_cur_time() + my_info->info_union->time_to_sleep;
	philo_is_speaking(my_info, my_info->my_id, "is sleeping");
	while (get_cur_time() < time_to_wakeup)
		usleep(300);
}
