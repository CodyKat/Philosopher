/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 04:45:39 by jaemjeon          #+#    #+#             */
/*   Updated: 2022/07/09 15:53:10 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>

# define TRUE 1
# define FALSE 0
# define SIZE_T_MAX 18446744073709551615ULL
# define INT_MAX 2147483647
# define INT_MIN (-2147483648)
# define ERR_NUM_OF_ARGC 1
# define ERR_NUM_OF_PHILO 2
# define ERR_TIME_TO_DIE 3
# define ERR_TIME_TO_EAT 4
# define ERR_TIME_TO_SLEEP 5
# define ERR_NUM_TO_MUST_EAT 6
# define UNLOCK 0
# define LOCK 1 

typedef struct s_union_info
{
	int				errnum;
	int				is_someone_dead;
	size_t			num_of_philo;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			num_each_philo_must_eat;
	int				*fork_status;
	size_t			time_to_start;
	pthread_t		**philo_arr;
	pthread_mutex_t	**fork_arr;
}	t_union_info;

typedef struct s_philo_info
{
	size_t			my_id;
	t_union_info	*union_info;

}	t_philo_info;

size_t
ft_atoul(char *str);
#endif