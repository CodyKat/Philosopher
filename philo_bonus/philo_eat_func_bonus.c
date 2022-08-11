/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat_func_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 19:22:55 by jaemjeon          #+#    #+#             */
/*   Updated: 2022/08/11 13:29:58 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

extern int static_sem_philo_last_meal_time[10];

void	philo_eat_with_no_option(t_philo *info_philo)
{
	size_t	time_to_finish_eat;
	int		sem_index;
	sem_t	*sem_time_last_meal;

	sem_index = info_philo->my_id - 1;
	sem_time_last_meal = \
		info_philo->sem_each_philo_time_last_meal[sem_index];
	sem_wait(sem_time_last_meal);
	static_sem_philo_last_meal_time[info_philo->my_id - 1]--;
	printf("sem_philo_last_meal_time[%zu] : %d\n", info_philo->my_id, static_sem_philo_last_meal_time[info_philo->my_id - 1]);
	info_philo->time_of_last_meal = get_cur_time();
	static_sem_philo_last_meal_time[info_philo->my_id - 1]++;
	printf("sem_philo_last_meal_time[%zu] : %d\n", info_philo->my_id, static_sem_philo_last_meal_time[info_philo->my_id - 1]);
	sem_post(sem_time_last_meal);
	sem_wait(sem_time_last_meal);
	static_sem_philo_last_meal_time[info_philo->my_id - 1]--;
	printf("sem_philo_last_meal_time[%zu] : %d\n", info_philo->my_id, static_sem_philo_last_meal_time[info_philo->my_id - 1]);
	time_to_finish_eat = \
			info_philo->time_of_last_meal + info_philo->info_union->time_to_eat;
	static_sem_philo_last_meal_time[info_philo->my_id - 1]++;
	printf("sem_philo_last_meal_time[%zu] : %d\n", info_philo->my_id, static_sem_philo_last_meal_time[info_philo->my_id - 1]);
	sem_post(sem_time_last_meal);
	philo_is_speaking(info_philo, get_time_stamp(info_philo->info_union), \
																"is eating");
	while (get_cur_time() < time_to_finish_eat)
		usleep(300);
	sem_post(info_philo->info_union->forks_set);
	sem_post(info_philo->info_union->forks_set);
}

void	philo_eat_with_option(t_philo *info_philo)
{
	size_t	time_to_finish_eat;
	int		sem_index;
	sem_t	*sem_time_last_meal;

	sem_index = info_philo->my_id - 1;
	sem_time_last_meal = \
		info_philo->sem_each_philo_time_last_meal[sem_index];
	sem_wait(sem_time_last_meal);
	info_philo->time_of_last_meal = get_cur_time();
	sem_post(sem_time_last_meal);
	sem_wait(sem_time_last_meal);
	time_to_finish_eat = \
			info_philo->time_of_last_meal + info_philo->info_union->time_to_eat;
	sem_post(sem_time_last_meal);
	philo_is_speaking(info_philo, get_time_stamp(info_philo->info_union), \
																"is eating");
	while (get_cur_time() < time_to_finish_eat)
		usleep(300);
	sem_post(info_philo->info_union->forks_set);
	sem_post(info_philo->info_union->forks_set);
	info_philo->eat_count++;
	if (info_philo->eat_count == \
						(int)info_philo->info_union->num_each_philo_must_eat)
		sem_post(info_philo->info_union->full_count);
}
