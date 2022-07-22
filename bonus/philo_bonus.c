/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 23:37:50 by jaemjeon          #+#    #+#             */
/*   Updated: 2022/07/23 01:47:55 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_process(t_philo *info_philo)
{
	printf("philo %zu is starting\n", info_philo->my_id);
	printf("%zu of union_info's address : %p\n", info_philo->my_id, info_philo->info_union);
	printf("%zu\n%zu\n", info_philo->info_union->num_of_philo, info_philo->info_union->time_to_die);
	sem_wait(info_philo->info_union->start_key);
	sem_post(info_philo->info_union->start_key);
	while (1)
	{
		pick_up_forks(info_philo);
		philo_eat(info_philo);
		philo_sleep(info_philo);
		philo_think(info_philo);
	}
	exit(1);
}
