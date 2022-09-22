/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: develoi89 <develoi89@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:09:05 by ealonso-          #+#    #+#             */
/*   Updated: 2022/09/22 13:35:08 by develoi89        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/philosophers.h"

void	printing(char *sms, t_vars *vars, int id)
{
	pthread_mutex_lock(&vars->writing);
	printf("\x1b[0m%lld %d %s\x1b[0m\n", (get_time() - vars->start_time), id, sms);
	if (vars->dd == 0)
		pthread_mutex_unlock(&vars->writing);
	else
	{
		sleep(1);
		free_all(vars);
	}
}

static void	think(t_vars *vars, int id)
{
	printing("is \x1b[32mthinking", vars, vars->philo[id].phnum);
}

static int	sleeping(t_vars *vars, int id)
{
	printing("is \x1b[36msleeping", vars, vars->philo[id].phnum);
	time_sleep (vars->args->tts);
	return (1);
}

static int	eat(t_vars *vars, int id)
{
	pthread_mutex_lock(&vars->cutl[vars->philo[id].right]);
	printing("is \x1b[33mhas taken a fork", vars, vars->philo[id].phnum);
	pthread_mutex_lock(&vars->cutl[vars->philo[id].left]);
	printing("is \x1b[33mhas taken a fork", vars, vars->philo[id].phnum);
	vars->philo[id].time = get_time();
	printing("is \x1b[35meating", vars, vars->philo[id].phnum);
	time_sleep (vars->args->tte);
	vars->philo[id].limiteat--;
	pthread_mutex_unlock(&vars->cutl[vars->philo[id].right]);
	pthread_mutex_unlock(&vars->cutl[vars->philo[id].left]);
	return (1);
}

void	*routine(void *var)
{
	t_vars	*vars;
	int		id;
	int		i;

	vars = (t_vars *)var;
	vars->dd = 0;
	id = vars->id;
	if (id % 2 == 0)
		time_sleep(200);
	vars->philo[id].time = get_time();
	while (vars->philo[id].time > (get_time() - vars->args->ttd)
		&& vars->dd == 0)
	{
		if (!eat(vars, id))
			break ;
		if (!sleeping(vars, id))
			break ;
		think(vars, id);
		if (vars->philo[id].limiteat == 0)
			break ;
	}
	i = -1;
	while (++i < vars->args->philos)
		pthread_mutex_unlock(&vars->cutl[i]);
	return (NULL);
}
