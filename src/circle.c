/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealonso- <ealonso-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:09:05 by ealonso-          #+#    #+#             */
/*   Updated: 2022/09/19 11:35:54 by ealonso-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/philosophers.h"

static void	printing(char *sms, t_vars *vars, int id)
{
	pthread_mutex_lock(&vars->writing);
	printf("%lld %d %s\n", get_time(), id, sms);
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
	printing("is thinking", vars, id);
}

static int	sleeping(t_vars *vars, int id)
{
	printing("is sleeping", vars, id);
	while (vars->philo[id].time > (get_time() - vars->args->tts))
	{
		if (!(vars->philo[id].time > (get_time() - vars->args->ttd)))
		{
			vars->dd = 1;
			printing("died", vars, id);
			return (0);
		}
	}
	return (1);
}

static int	eat(t_vars *vars, int id)
{
	pthread_mutex_lock(&vars->cutl[vars->philo[id].right]);
	pthread_mutex_lock(&vars->cutl[vars->philo[id].left]);
	printing("is eating", vars, id);
	while (vars->philo[id].time > (get_time() - vars->args->tte))
	{
		if (!(vars->philo[id].time > (get_time() - vars->args->ttd)))
		{
			vars->dd = 1;
			printing("died", vars, id);
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
	}
	i = -1;
	// while (++i < vars->args->philos)
	// 	pthread_mutex_unlock(&vars->cutl[i]);
	return (NULL);
}
