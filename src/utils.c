/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealonso- <ealonso-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 13:01:04 by ealonso-          #+#    #+#             */
/*   Updated: 2022/10/03 18:31:10 by ealonso-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	printing(char *sms, t_vars *vars, int id)
{
	pthread_mutex_lock(&vars->writing);
	printf("\x1b[0m%lld %d %s\x1b[0m\n",
		(get_time() - vars->start_time), id, sms);
	if (vars->dd == 0)
	{
		pthread_mutex_unlock(&vars->writing);
		return (1);
	}
	else
	{
		free_all(vars);
		usleep(400);
		return (0);
	}
}

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

int	free_all(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->args->philos)
	{
		pthread_mutex_unlock(&vars->cutl[i]);
		pthread_mutex_destroy(&vars->cutl[i]);
		i++;
	}
	pthread_mutex_unlock(&vars->writing);
	pthread_mutex_destroy(&vars->writing);
	pthread_mutex_destroy(&vars->dead);
	if (vars->cutl)
		free(vars->cutl);
	if (vars->args)
		free(vars->args);
	if (vars->philo)
		free(vars->philo);
	if (vars->threads)
		free(vars->threads);
	if (vars)
		free(vars);
	return (0);
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
		usleep(i / 2);
}
