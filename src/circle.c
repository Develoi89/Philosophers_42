/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealonso- <ealonso-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:09:05 by ealonso-          #+#    #+#             */
/*   Updated: 2022/10/06 17:42:45 by ealonso-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/philosophers.h"

static int	think(t_philo *philo)
{
	if (philo->vars->dd == 0 && philo->vars->done != philo->vars->args->philos)
		printing("is \x1b[32mthinking", philo);
	else
		return (0);
	return (1);
}

static int	sleeping(t_philo *philo)
{
	if (philo->vars->dd == 0 && philo->vars->done != philo->vars->args->philos)
	{
		printing("is \x1b[36msleeping", philo);
		time_sleep (philo->vars->args->tts);
	}
	else
		return (0);
	return (1);
}

static int	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->vars->cutl[philo->right]);
	if (philo->vars->dd == 0)
		printing("is \x1b[33mhas taken a fork", philo);
	if (philo->vars->args->philos <= 1)
		return (0);
	pthread_mutex_lock(&philo->vars->cutl[philo->left]);
	if (philo->vars->dd == 0)
		printing("is \x1b[33mhas taken a fork", philo);
	philo->meals++;
	if (philo->vars->dd == 0)
		printing("is \x1b[35meating", philo);
	philo->time = get_time();
	time_sleep (philo->vars->args->tte);
	if (philo->vars->dd != 0)
		return (0);
	if (philo->vars->args->param == 6)
		philo->limiteat--;
	pthread_mutex_unlock(&philo->vars->cutl[philo->right]);
	pthread_mutex_unlock(&philo->vars->cutl[philo->left]);
	return (1);
}

int	circle(t_philo *philo)
{
	while (philo->vars->dd == 0)
	{
		if (philo->vars->args->param == 6 && philo->limiteat == 0)
			break ;
		if (!eat(philo))
			break ;
		if (!sleeping(philo))
			break ;
		if (!think(philo))
			break ;
	}
	return (1);
}

void	*routine(void *philos)
{
	t_philo	*philo;

	philo = (t_philo *)philos;
	philo->vars->init++;
	while (philo->vars->dd == 0)
		if (philo->vars->init == philo->vars->args->philos
			&& philo->vars->start_time != 0)
			break ;
	philo->time = get_time();
	if (philo->phnum % 2 == 0)
		time_sleep(philo->vars->args->tte);
	circle(philo);
	return (NULL);
}
