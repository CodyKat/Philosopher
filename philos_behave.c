/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_behave.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 19:33:18 by jaemjeon          #+#    #+#             */
/*   Updated: 2022/07/12 19:36:11 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_someone_dead(t_union_info *info)
{
	return (info->is_someone_dead);
}

void	get_my_right_fork(t_philo_info *info)
{
	struct timeval	cur_time;
	size_t			time_to_start_in_ms;
	size_t			cur_time_in_ms;
	size_t			passed_time_in_ms;

	time_to_start_in_ms = info->union_info->time_to_start;
	gettimeofday(&cur_time, NULL);
	cur_time_in_ms = timeval_to_ms(cur_time);
	passed_time_in_ms = cur_time_in_ms - time_to_start_in_ms;
	pthread_mutex_lock(info->union_info->fork_arr[info->right_fork_id]);
	info->union_info->fork_status[info->right_fork_id] = 1;
	// control_fork_status(info->union_info, info->right_fork_id, LOCK);
	if (!is_someone_dead(info->union_info))
		philo_is_speaking(info, passed_time_in_ms, "has taken a fork", FORK);
}

void	get_my_left_fork(t_philo_info *info)
{
	struct timeval	cur_time;
	size_t			time_to_start_in_ms;
	size_t			cur_time_in_ms;
	size_t			passed_time_in_ms;

	time_to_start_in_ms = info->union_info->time_to_start;
	gettimeofday(&cur_time, NULL);
	cur_time_in_ms = timeval_to_ms(cur_time);
	passed_time_in_ms = cur_time_in_ms - time_to_start_in_ms;
	pthread_mutex_lock(info->union_info->fork_arr[info->left_fork_id]);
	info->union_info->fork_status[info->left_fork_id] = 1;
	// control_fork_status(info->union_info, info->left_fork_id, LOCK);
		philo_is_speaking(info, passed_time_in_ms, "has taken a fork", FORK);
}

void	philo_eat(t_philo_info *info)
{
	struct timeval	cur_time;
	size_t			time_to_start_in_ms;
	size_t			cur_time_in_ms;
	size_t			passed_time_in_ms;

	time_to_start_in_ms = info->union_info->time_to_start;
	gettimeofday(&cur_time, NULL);
	cur_time_in_ms = timeval_to_ms(cur_time);
	info->time_of_last_meal = cur_time_in_ms;
	passed_time_in_ms = cur_time_in_ms - time_to_start_in_ms;
	if (!is_someone_dead(info->union_info))
		philo_is_speaking(info, passed_time_in_ms, "is eating", EAT);
	usleep(info->union_info->time_to_eat * 1000);
	info->union_info->fork_status[info->left_fork_id] = 0;
	info->union_info->fork_status[info->right_fork_id] = 0;
	// control_fork_status(info->union_info, info->right_fork_id, UNLOCK);
	// control_fork_status(info->union_info, info->left_fork_id, UNLOCK);
	pthread_mutex_unlock(info->union_info->fork_arr[info->right_fork_id]);
	pthread_mutex_unlock(info->union_info->fork_arr[info->left_fork_id]);
}

void	philo_sleep(t_philo_info *info)
{
	struct timeval	cur_time;
	size_t			time_to_start_in_ms;
	size_t			cur_time_in_ms;
	size_t			passed_time_in_ms;

	time_to_start_in_ms = info->union_info->time_to_start;
	gettimeofday(&cur_time, NULL);
	cur_time_in_ms = timeval_to_ms(cur_time);
	passed_time_in_ms = cur_time_in_ms - time_to_start_in_ms;
	if (!is_someone_dead(info->union_info))
		philo_is_speaking(info, passed_time_in_ms, "is sleeping", SLEEP);
	usleep(info->union_info->time_to_sleep * 1000);
}

void	philo_think(t_philo_info *info)
{
	struct timeval	cur_time;
	size_t			time_to_start_in_ms;
	size_t			cur_time_in_ms;
	size_t			passed_time_in_ms;

	time_to_start_in_ms = info->union_info->time_to_start;
	gettimeofday(&cur_time, NULL);
	cur_time_in_ms = timeval_to_ms(cur_time);
	passed_time_in_ms = cur_time_in_ms - time_to_start_in_ms;
	if (!is_someone_dead(info->union_info))
		philo_is_speaking(info, passed_time_in_ms, "is thinking", THINK);
}