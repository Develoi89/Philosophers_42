/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealonso- <ealonso-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:09:05 by ealonso-          #+#    #+#             */
/*   Updated: 2022/09/07 17:53:24 by ealonso-         ###   ########.fr       */
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
			usleep(20);
			pthread_mutex_lock(&vars->writing);
			printf("\033[1;31mPhilosopher number %d is dead\n", id);
			return (0);
		}
	}
	return (1);
}

static int	eat(t_vars *vars, int id)
{
	pthread_mutex_lock(&vars->cutl[vars->philo[id].right]);
	pthread_mutex_lock(&vars->cutl[vars->philo[id].left]);
	pthread_mutex_lock(&vars->writing);
	printf("Philosopher %d is eating\n", id);
	pthread_mutex_unlock(&vars->writing);
	while (vars->philo[id].time > (get_time() - vars->args->tte))
	{
		if (!(vars->philo[id].time > (get_time() - vars->args->ttd)))
		{
			usleep(20);
			pthread_mutex_lock(&vars->writing);
			printf("\033[1;31mPhilosopher number %d is dead\n", id);
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
	int		i;

	vars = (t_vars *)var;
	id = vars->id;
	// if (id % 2 == 0)
	// 	time_sleep(20);
	// usleep (20);
	vars->philo[id].time = get_time();
	while (vars->philo[id].time > (get_time() - vars->args->ttd))
	{
		if (!eat(vars, id))
			break ;
		if (!sleeping(vars, id))
			break ;
	}
	write(1, "a", 1);
	pthread_mutex_unlock(&vars->writing);
	i = -1;
	while (i < vars->args->philos)
		pthread_mutex_unlock(&vars->cutl[i]);
	return (NULL);
}
