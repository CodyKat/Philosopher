/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 00:03:13 by jaemjeon          #+#    #+#             */
/*   Updated: 2022/08/10 03:15:48 by jaemjeon         ###   ########.fr       */
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
		if (argc == 6)
		{
			info_union->has_optional_arg = TRUE;
			info_union->num_each_philo_must_eat = ft_atoul_check_range(argv[5]);
		}
		if (paras_is_in_valid_range(info_union) == ERROR)
			ft_error(info_union, NULL);
		info_union->philo_pid_arr = \
					(pid_t *)ft_calloc(sizeof(int) * info_union->num_of_philo);
		if (info_union->philo_pid_arr == NULL)
			ft_error(info_union, NULL);
		return ;
	}
	ft_error(info_union, NULL);
}

void	make_each_philo_sem(t_union *info_union, t_philo *info_philo)
{
	int		n_philo;
	char	*str_philo_id;
	char	*str_sem_name;

	n_philo = -1;
	while (++n_philo < (int)info_union->num_of_philo)
	{
		str_philo_id = ft_itoa(n_philo + 1);
		str_sem_name = ft_strjoin("sem_philo_time_last_meal", str_philo_id);
		sem_unlink(str_sem_name);
		info_philo->sem_each_philo_time_last_meal[n_philo] = \
			sem_open(str_sem_name, O_CREAT, S_IRWXG, 1);
		free(str_sem_name);
		str_sem_name = ft_strjoin("sem_eat_count", str_philo_id);
		sem_unlink(str_sem_name);
		info_philo->sem_eat_count[n_philo] = \
				sem_open(str_sem_name, O_CREAT, S_IRWXG, 1);
		free(str_sem_name);
		free(str_philo_id);
		if (info_philo->sem_each_philo_time_last_meal[n_philo] == SEM_FAILED \
			|| info_philo->sem_eat_count[n_philo] == SEM_FAILED)
			ft_error(info_union, info_philo);
	}
}

void	init_after_parsing(t_union *info_union, t_philo *info_philo, int argc)
{
	info_philo->sem_each_philo_time_last_meal = \
		(sem_t **)malloc(sizeof(sem_t *) * info_union->num_of_philo);
	info_philo->sem_eat_count = \
		(sem_t **)malloc(sizeof(sem_t *) * info_union->num_of_philo);
	info_union->forks_set = sem_open("forks_set", O_CREAT, S_IRWXG, \
												info_union->num_of_philo / 2);
	if (info_union->forks_set == SEM_FAILED \
		|| info_philo->sem_eat_count == NULL \
		||info_philo->sem_each_philo_time_last_meal == NULL)
		ft_error(info_union, info_philo);
	make_each_philo_sem(info_union, info_philo);
	if (argc == 6)
		info_union->has_optional_arg = TRUE;
	else
		info_union->has_optional_arg = FALSE;
}
