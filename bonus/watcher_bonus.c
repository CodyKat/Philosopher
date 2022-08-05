/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 17:21:53 by jaemjeon          #+#    #+#             */
/*   Updated: 2022/08/05 15:54:15 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*f_watcher_is_all_full(void	*info_union)
{
	t_union	*info;
	int		n_philo;

	info = (t_union *)info_union;
	n_philo = -1;
	while (++n_philo < (int)info->num_of_philo)
		sem_wait(info->full_count);
	if (info->is_someone_dead == FALSE)
	{
		sem_wait(info->voice);
		printf("all philo is full\n");
	}
	sem_post(info->dead_flag);
	sem_post(info->end_game);
	return (NULL);
}

void	*f_watcher_is_someone_dead(void *info_union)
{
	t_union	*info;
	int		n_philo;

	n_philo = -1;
	info = (t_union *)info_union;
	sem_wait(info->dead_flag);
	info->is_someone_dead = TRUE;
	while (++n_philo < (int)info->num_of_philo)
		sem_post(info->full_count);
	sem_post(info->end_game);
	return (NULL);
}
