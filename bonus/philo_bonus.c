/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 23:37:50 by jaemjeon          #+#    #+#             */
/*   Updated: 2022/07/23 02:31:13 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_process(t_philo *info_philo)
{
	sem_wait(info_philo->info_union->start_key);
	sem_post(info_philo->info_union->start_key);
	while (1)
	{
		pick_up_forks(info_philo);
		philo_eat(info_philo);
		philo_sleep(info_philo);
		philo_think(info_philo);
	}
}
