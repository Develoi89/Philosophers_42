/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: develoi89 <develoi89@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 13:01:04 by ealonso-          #+#    #+#             */
/*   Updated: 2022/08/03 13:15:34 by develoi89        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	comprove(char **argv, int argc)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (errors("\033[1;31mOnly numeric arguments are valid\n"));
			j++;
		}
		i++;
	}
	if (argc != 5 && argc != 6)
		return (errors("\033[1;31mInvalid num of arguents!\n"));
	return (1);
}

void free_all(t_vars *vars)
{
	int i;

	i = 0;
	while (i < vars->args->philos)
	{
		pthread_mutex_destroy(&vars->cutl[i]);
		i++;
	}
	pthread_mutex_destroy(&vars->writing);
	pthread_mutex_destroy(&vars->dead);
	free(vars->cutl);
	free(vars->args);
	free(vars->philo);
	free(vars);
}
