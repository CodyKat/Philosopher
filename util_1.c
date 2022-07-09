/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 04:53:21 by jaemjeon          #+#    #+#             */
/*   Updated: 2022/07/09 06:08:05 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(char c)
{
	if (('0' <= c) && (c <= '9'))
		return (TRUE);
	else
		return (FALSE);
	
}

size_t ft_atoul(char *str)
{
	size_t	result;

	result = 0;
	while (*str)
	{
		if (ft_isdigit(*str) == FALSE)
			return (SIZE_T_MAX);
		result *= 10;
		result += (*str) - '0';
		str++;
	}
	return (result);
}