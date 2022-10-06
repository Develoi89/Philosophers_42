/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealonso- <ealonso-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 13:01:04 by ealonso-          #+#    #+#             */
/*   Updated: 2022/10/06 17:45:23 by ealonso-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	printing(char *sms, t_philo *philo)
{
	pthread_mutex_lock(&philo->vars->writing);
	if (philo->vars->dd == 0)
		printf("\x1b[0m%lld %d %s\x1b[0m\n",
			(get_time() - philo->vars->start_time), philo->phnum, sms);
	pthread_mutex_unlock(&philo->vars->writing);
	return (1);
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

int	free_all(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->vars->args->philos)
	{
		pthread_mutex_unlock(&philo->vars->cutl[i]);
		pthread_mutex_destroy(&philo->vars->cutl[i]);
		i++;
	}
	pthread_mutex_unlock(&philo->vars->writing);
	pthread_mutex_destroy(&philo->vars->writing);
	pthread_mutex_destroy(&philo->vars->dead);
	if (philo->vars->cutl)
		free(philo->vars->cutl);
	if (philo->vars->args)
		free(philo->vars->args);
	if (philo->vars->threads)
		free(philo->vars->threads);
	if (philo->vars)
		free(philo->vars);
	if (philo)
		free(philo);
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
