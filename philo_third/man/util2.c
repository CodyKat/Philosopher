/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 00:24:35 by jaemjeon          #+#    #+#             */
/*   Updated: 2022/07/14 00:58:46 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	 paras_is_in_valid_range(t_union *info_union, int argc)
{
	if ((info_union->num_of_philo == 0) || (info_union->time_to_die == 0)\
		|| (info_union->time_to_eat == 0) || (info_union->time_to_sleep == 0) ||
		(info_union->num_of_philo > INT_MAX) || \
		(info_union->time_to_die > INT_MAX) || \
		(info_union->time_to_eat > INT_MAX) || \
		(info_union->time_to_sleep > INT_MAX))
		return (ERROR);
	if ((argc == 6) && ((info_union->num_each_philo_must_eat == 0) || \
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
