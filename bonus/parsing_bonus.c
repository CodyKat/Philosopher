/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 00:03:13 by jaemjeon          #+#    #+#             */
/*   Updated: 2022/07/31 18:12:43 by jaemjeon         ###   ########.fr       */
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
		{
			info_union->has_optional_arg = TRUE;
			info_union->num_each_philo_must_eat = ft_atoul_check_range(argv[5]);
		}
		if (paras_is_in_valid_range(info_union) == ERROR)
			ft_error(info_union);
		info_union->philo_pid_arr = \
					(pid_t *)ft_calloc(sizeof(int) * info_union->num_of_philo);
		if (info_union->philo_pid_arr == NULL)
			ft_error(info_union);
		return ;
	}
	ft_error(info_union);
}

void	init_after_parsing(t_union *info_union, int argc)
{
	info_union->forks_set = sem_open("forks_set", O_CREAT, S_IRWXG, \
												info_union->num_of_philo / 2);
	if (info_union->forks_set == SEM_FAILED)
		ft_error(info_union);
	if (argc == 6)
		info_union->has_optional_arg = TRUE;
	else
		info_union->has_optional_arg = FALSE;
}
