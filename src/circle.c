/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealonso- <ealonso-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:09:05 by ealonso-          #+#    #+#             */
/*   Updated: 2022/09/06 17:08:11 by ealonso-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/philosophers.h"

static int	sleeping(t_vars *vars, int id)
{
	pthread_mutex_lock(&vars->writing);
	printf("Philosopher %d is sleeping\n", id);
	pthread_mutex_unlock(&vars->writing);
	while (vars->philo[id].time > (get_time() - vars->args->tts))
	{
		if (!(vars->philo[id].time > (get_time() - vars->args->ttd)))
		{
			pthread_mutex_lock(&vars->writing);
			printf("Philosopher number %d is dead\n", id);
			pthread_mutex_unlock(&vars->writing);
			return (0);
		}
	}
	return (1);
}

static int	eat(t_vars *vars, int id)
{
	pthread_mutex_lock(&vars->writing);
	printf("Philosopher %d is eating\n", id);
	pthread_mutex_unlock(&vars->writing);
	pthread_mutex_lock(&vars->cutl[vars->philo[id].right]);
	pthread_mutex_lock(&vars->cutl[vars->philo[id].left]);
	while (vars->philo[id].time > (get_time() - vars->args->tte))
	{
		if (!(vars->philo[id].time > (get_time() - vars->args->ttd)))
		{
			pthread_mutex_lock(&vars->writing);
			printf("Philosopher number %d is dead\n", id);
			pthread_mutex_unlock(&vars->writing);
			return (0);
		}
	}
	pthread_mutex_unlock(&vars->cutl[vars->philo[id].right]);
	pthread_mutex_unlock(&vars->cutl[vars->philo[id].left]);
	vars->philo[id].time = get_time();
	return (1);
}

void	*routine(void *var)
{
	t_vars	*vars;
	int		id;

	vars = (t_vars *)var;
	id = vars->id;
	// if (id % 2 == 0)
	// 	time_sleep(20);
	vars->philo[id].time = get_time();
	while (vars->philo[id].time > (get_time() - vars->args->ttd))
	{
		if (!eat(vars, id))
			break ;
		if (!sleeping(vars, id))
			break ;
	}
	pthread_mutex_lock(&vars->writing);
	printf("philo %d is dead", id);
	pthread_mutex_unlock(&vars->writing);
	return (NULL);
}
