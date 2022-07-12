/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behave.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 03:22:12 by jaemjeon          #+#    #+#             */
/*   Updated: 2022/07/13 04:00:37 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_my_rigth_fork(t_philo *info_philo)
{
	t_union	*info_union;

	info_union = info_philo->info_union;
	pthread_mutex_lock(&info_union->fork_key[info_philo->my_right_fork_id]);
	info_union->fork_status[info_philo->my_right_fork_id] = LOCK;
	ft_print_log(info_philo, get_cur_time(), "has taken a fork", FALSE);
}

void	get_my_left_fork(t_philo *info_philo)
{
	t_union	*info_union;

	info_union = info_philo->info_union;
	pthread_mutex_lock(&info_union->fork_key[info_philo->my_left_fork_id]);
	info_union->fork_status[info_philo->my_left_fork_id] = LOCK;
	ft_print_log(info_philo, get_cur_time(), "has taken a fork", FALSE);
}

void	philo_eat(t_philo *info_philo)
{
	t_union	*info_union;

	info_union = info_philo->info_union;
	ft_print_log(info_philo, get_cur_time(), "is eating", FALSE);
	info_philo->time_last_meal = get_cur_time();
	usleep(info_union->time_to_eat * 1000);
	info_union->fork_status[info_philo->my_left_fork_id] = UNLOCK;
	pthread_mutex_unlock(&info_union->fork_key[info_philo->my_left_fork_id]);
	info_union->fork_status[info_philo->my_right_fork_id] = UNLOCK;
	pthread_mutex_unlock(&info_union->fork_key[info_philo->my_right_fork_id]);
}

void	philo_sleep(t_philo *info_philo)
{
	ft_print_log(info_philo, get_cur_time(), "is sleeping", FALSE);
	usleep(info_philo->info_union->time_to_sleep * 1000);
}

void	philo_think(t_philo *info_philo)
{
	ft_print_log(info_philo, get_cur_time(), "is thinking", FALSE);
}
