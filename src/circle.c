/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealonso- <ealonso-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:09:05 by ealonso-          #+#    #+#             */
/*   Updated: 2022/09/27 16:50:54 by ealonso-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/philosophers.h"

static void	think(t_vars *vars, int id)
{
	if (vars->dd == 0 && vars->done != vars->args->philos)
		printing("is \x1b[32mthinking", vars, vars->philo[id].phnum);
}

static int	sleeping(t_vars *vars, int id)
{
	if (vars->dd == 0 && vars->done != vars->args->philos)
	{
		printing("is \x1b[36msleeping", vars, vars->philo[id].phnum);
		time_sleep (vars->args->tts);
	}
	return (1);
}

static void	eat(t_vars *vars, int id)
{
	pthread_mutex_lock(&vars->cutl[vars->philo[id].right]);
	printing("is \x1b[33mhas taken a fork", vars, vars->philo[id].phnum);
	pthread_mutex_lock(&vars->cutl[vars->philo[id].left]);
	printing("is \x1b[33mhas taken a fork", vars, vars->philo[id].phnum);
	vars->philo[id].time = get_time();
	printing("is \x1b[35meating", vars, vars->philo[id].phnum);
	time_sleep (vars->args->tte);
	if (vars->args->param == 6)
		vars->philo[id].limiteat--;
	pthread_mutex_unlock(&vars->cutl[vars->philo[id].right]);
	pthread_mutex_unlock(&vars->cutl[vars->philo[id].left]);
}

void	circle(t_vars *vars, int id)
{
	while (vars->philo[id].time > (get_time() - vars->args->ttd)
		&& vars->dd == 0)
	{
		eat(vars, id);
		sleeping(vars, id);
		think(vars, id);
		if (vars->args->param == 6 && vars->philo[id].limiteat == 0)
			break ;
	}
}

void	*routine(void *var)
{
	t_vars	*vars;
	int		id;
	int		i;

	vars = (t_vars *)var;
	vars->init++;
	id = vars->id;
	while (42)
		if (vars->init == vars->args->philos && vars->start_time)
			break ;
	if (id % 2 != 0)
		time_sleep(vars->args->tte / 2);
	vars->philo[id].time = get_time();
	circle(vars, id);
	i = -1;
	while (++i < vars->args->philos)
		pthread_mutex_unlock(&vars->cutl[i]);
	return (NULL);
}
