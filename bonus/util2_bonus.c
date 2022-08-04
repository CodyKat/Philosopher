/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 00:24:35 by jaemjeon          #+#    #+#             */
/*   Updated: 2022/08/04 23:13:10 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	paras_is_in_valid_range(t_union *info_union)
{
	if ((info_union->num_of_philo == 0) || (info_union->time_to_die == 0) \
		|| (info_union->time_to_eat == 0) || (info_union->time_to_sleep == 0) \
		|| (info_union->num_of_philo > INT_MAX) \
		|| (info_union->time_to_die > INT_MAX) \
		|| (info_union->time_to_eat > INT_MAX) \
		|| (info_union->time_to_sleep > INT_MAX))
		return (ERROR);
	if ((info_union->has_optional_arg == TRUE) && \
				((info_union->num_each_philo_must_eat == 0) || \
				(info_union->num_each_philo_must_eat > INT_MAX)))
		return (ERROR);
	return (TRUE);
}

void	*ft_calloc(size_t size)
{
	void	*p_mem;

	p_mem = malloc(size);
	if (p_mem != NULL)
		memset(p_mem, 0, size);
	return (p_mem);
}

void	ft_fork_error(t_union *info_union)
{
	kill_all_philos(info_union);
	ft_error(info_union);
}

int	ft_wexitstatus(int status)
{
	return ((status >> 8) & 0x000000ff);
}

void	close_all_sem(t_union *info_union)
{
	int	index;

	index = -1;
	if (info_union->sem_each_philo_time_last_meal != NULL)
	{
		while (++index < (int)info_union->num_of_philo)
			sem_close(info_union->sem_each_philo_time_last_meal[index]);
		free(info_union->sem_each_philo_time_last_meal);
	}
	sem_close(info_union->forks_set);
	sem_close(info_union->voice);
	sem_close(info_union->start_key);
	sem_close(info_union->full_count);
	sem_close(info_union->dead_flag);
	sem_close(info_union->end_game);
}
