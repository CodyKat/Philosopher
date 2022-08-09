/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 17:21:53 by jaemjeon          #+#    #+#             */
/*   Updated: 2022/08/10 05:00:55 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*f_watcher_is_all_full(void	*union_para)
{
	t_union	*info_union;
	int		n_philo;

	info_union = (t_union *)union_para;
	n_philo = -1;
	while (++n_philo < (int)info_union->num_of_philo)
		sem_wait(info_union->full_count);
	sem_wait(info_union->sem_is_someone_dead);
	if (info_union->is_someone_dead == FALSE)
	{
		sem_wait(info_union->voice);
		printf("all philo is full\n");
		sem_post(info_union->sem_is_someone_dead);
	}
	sem_post(info_union->sem_is_someone_dead);
	sem_post(info_union->dead_flag);
	sem_post(info_union->end_game);
	return (NULL);
}

void	*f_watcher_is_someone_dead(void *union_para)
{
	t_union	*info_union;
	int		n_philo;

	info_union = (t_union *)union_para;
	sem_wait(info_union->dead_flag);
	sem_wait(info_union->sem_is_someone_dead);
	info_union->is_someone_dead = TRUE;
	sem_post(info_union->sem_is_someone_dead);
	n_philo = -1;
	while (++n_philo < (int)info_union->num_of_philo)
		sem_post(info_union->full_count);
	sem_post(info_union->end_game);
	return (NULL);
}
