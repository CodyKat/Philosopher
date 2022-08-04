/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 17:21:53 by jaemjeon          #+#    #+#             */
/*   Updated: 2022/08/04 17:47:54 by jaemjeon         ###   ########.fr       */
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
	printf("all philo is full\n");
	sem_post(info->end_game);
	sem_post(info->dead_flag);
	return (NULL);
}

void	*f_watcher_is_someone_dead(void *info_union)
{
	t_union	*info;

	info = (t_union *)info_union;
	sem_wait(info->dead_flag);
	sem_post(info->end_game);
	return (NULL);
}
