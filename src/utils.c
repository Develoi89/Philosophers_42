/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealonso- <ealonso-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 13:01:04 by ealonso-          #+#    #+#             */
/*   Updated: 2022/09/23 10:45:17 by ealonso-         ###   ########.fr       */
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
				return (errors
					("\033[1;31mOnly positive numeric arguments are valid\n"));
			j++;
		}
		i++;
	}
	if (argc != 5 && argc != 6)
		return (errors("\033[1;31mInvalid num of arguents!\n"));
	return (1);
}

void	free_all(t_vars *vars)
{
	int	i;

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
	if (vars->threads)
		free(vars->threads);
	free(vars);
	exit(0);
}

long long int	get_time(void)
{
	struct timeval	i;

	gettimeofday(&i, NULL);
	return ((i.tv_sec * 1000) + (i.tv_usec / 1000));
}

void	time_sleep(int i)
{
	long long int	now;

	now = get_time();
	while (i > get_time() - now)
		usleep(50);
}
