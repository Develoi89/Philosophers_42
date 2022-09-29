/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealonso- <ealonso-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 15:03:50 by ealonso-          #+#    #+#             */
/*   Updated: 2022/09/29 17:11:17 by ealonso-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/philosophers.h"

void	rationing(t_vars *vars, int id)
{
	int	j;

	j = vars->args->philos;
	if (id > 0 && id < j - 1)
	{
		while (42)
			if ((vars->philo[id].meals <= vars->philo[id + 1].meals
				|| vars->philo[id].meals <= vars->philo[id - 1].meals) || vars->dd != 0)
				break ;
	}
	if (id == 0)
	{
		while (42)
			if ((vars->philo[id].meals <= vars->philo[1].meals
				|| vars->philo[id].meals <= vars->philo[j - 1].meals) || vars->dd != 0)
				break ;
	}
	if (id == j - 1)
	{
		while (42)
			if ((vars->philo[id].meals <= vars->philo[0].meals
				|| vars->philo[id].meals <= vars->philo[id - 1].meals) || vars->dd != 0)
				break ;
	}
}
