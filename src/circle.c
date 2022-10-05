/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealonso- <ealonso-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:09:05 by ealonso-          #+#    #+#             */
/*   Updated: 2022/10/05 16:32:01 by ealonso-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/philosophers.h"

static int	think(t_vars *vars, int id)
{
	if (vars->dd == 0 && vars->done != vars->args->philos)
		printing("is \x1b[32mthinking", vars, vars->philo[id].phnum);
	else
		return (0);
	return (1);
}

static int	sleeping(t_vars *vars, int id)
{
	if (vars->dd == 0 && vars->done != vars->args->philos)
	{
		printing("is \x1b[36msleeping", vars, vars->philo[id].phnum);
		time_sleep (vars->args->tts);
	}
	else
		return (0);
	return (1);
}

static int	eat(t_vars *vars, int id)
{
	pthread_mutex_lock(&vars->cutl[vars->philo[id].right]);
	if (vars->dd == 0)
		printing("is \x1b[33mhas taken a fork", vars, vars->philo[id].phnum);
	if (vars->args->philos <= 1)
		return (0);
	pthread_mutex_lock(&vars->cutl[vars->philo[id].left]);
	if (vars->dd == 0)
		printing("is \x1b[33mhas taken a fork", vars, vars->philo[id].phnum);
	vars->philo[id].meals++;
	if (vars->dd == 0)
		printing("is \x1b[35meating", vars, vars->philo[id].phnum);
	vars->philo[id].time = get_time();
	time_sleep (vars->args->tte);
	if (vars->dd != 0)
		return (0);
	if (vars->args->param == 6)
		vars->philo[id].limiteat--;
	pthread_mutex_unlock(&vars->cutl[vars->philo[id].right]);
	pthread_mutex_unlock(&vars->cutl[vars->philo[id].left]);
	return (1);
}

int	circle(t_vars *vars, int id)
{
	while (vars->dd == 0)
	{
		if (!eat(vars, id) || !sleeping(vars, id) || !think(vars, id))
		{
			usleep (42);
			break ;
		}
		if (vars->args->param == 6 && vars->philo[id].limiteat == 0)
			break ;
	}
	return (1);
}

void	*routine(void *temp)
{
	t_tmp	*tmp;
	int		id;

	tmp = (t_tmp *)temp;
	tmp->vars->init++;
	id = tmp->id;
	while (tmp->vars->dd == 0)
		if (tmp->vars->init == tmp->vars->args->philos
			&& tmp->vars->start_time != 0)
			break ;
	tmp->vars->philo[id].time = get_time();
	if (tmp->vars->philo[id].phnum % 2 == 0)
		time_sleep(tmp->vars->args->tte);
	circle(tmp->vars, id);
	return (NULL);
}
