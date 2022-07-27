/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 00:03:13 by jaemjeon          #+#    #+#             */
/*   Updated: 2022/07/27 21:27:33 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	parsing(t_union *info_union, int argc, char **argv)
{
	if ((argc == 5) || (argc == 6))
	{
		info_union->num_of_philo = ft_atoul_check_range(argv[1]);
		info_union->time_to_die = ft_atoul_check_range(argv[2]);
		info_union->time_to_eat = ft_atoul_check_range(argv[3]);
		info_union->time_to_sleep = ft_atoul_check_range(argv[4]);
		info_union->num_each_philo_must_eat = -1;
		if (argc == 6)
			info_union->num_each_philo_must_eat = ft_atoul_check_range(argv[5]);
		if (paras_is_in_valid_range(info_union, argc) == ERROR)
			ft_error();
		info_union->philo_pid_arr = \
					(pid_t *)malloc(sizeof(int) * info_union->num_of_philo);
		if (info_union->philo_pid_arr == NULL)
			ft_error();
		return ;
	}
	ft_error();
}
