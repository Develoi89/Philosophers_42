/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealonso- <ealonso-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:05:22 by ealonso-          #+#    #+#             */
/*   Updated: 2022/10/12 12:05:38 by ealonso-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/philosophers.h"

int	any_dead(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->args->philos && vars->dd == 0)
	{
		pthread_mutex_lock(&vars->dead);
		if (vars->philo[i].time != 0
			&& vars->args->ttd < (get_time() - vars->philo[i].time))
		{
			if (vars->dd == 0)
				printing("\x1b[41mdied", &vars->philo[i]);
			vars->dd = 1;
			return (0);
		}
		if (vars->args->param == 6 && vars->philo[i].limiteat == 0
			&& vars->args->limiteat > 0)
			vars->done++;
		if (vars->done == vars->args->philos)
			return (0);
		pthread_mutex_unlock(&vars->dead);
		i++;
	}
	return (1);
}

static int	start(t_vars *vars, int i)
{
	vars->threads = (pthread_t *)malloc(sizeof(pthread_t) * vars->args->philos);
	if (!vars->threads)
		return (errors("\033[1;31mthreads malloc failed!\n"));
	while (++i < vars->args->philos)
	{
		pthread_create(&(vars->threads[i]), NULL, &routine, &vars->philo[i]);
		usleep (60);
	}
	while (42)
	{
		if (vars->init >= vars->args->philos)
		{
			vars->start_time = get_time();
			break ;
		}
	}
	while (42)
		if (!any_dead(vars))
			break ;
	while (--i >= 0)
		pthread_join(vars->threads[i], NULL);
	return (1);
}

static int	initphilos(t_vars *vars)
{
	int	i;

	i = 0;
	vars->dd = 0;
	vars->philo = (t_philo *)malloc(sizeof(t_philo) * vars->args->philos);
	if (!vars->philo)
		return (errors("\033[1;31mphilos malloc failed!\n"));
	while (i < vars->args->philos)
	{
		vars->philo[i].phnum = i + 1;
		vars->philo[i].right = i;
		if (i != vars->args->philos - 1)
			vars->philo[i].left = i + 1;
		else
			vars->philo[i].left = 0;
		vars->philo[i].limiteat = vars->args->limiteat;
		vars->philo[i].vars = vars;
		i++;
	}
	return (0);
}

static int	initargs(t_vars *vars, int argc, char **argv, int i)
{
	i++;
	vars->done = 0;
	vars->init = 0;
	vars->args = malloc(sizeof(t_args));
	if (!vars->args)
		return (errors("\033[1;31margs malloc failed!\n"));
	vars->args->philos = ft_atoi(argv[1]);
	vars->args->ttd = ft_atoi(argv[2]);
	vars->args->tte = ft_atoi(argv[3]);
	vars->args->tts = ft_atoi(argv[4]);
	vars->args->limiteat = -1;
	if (argc == 6)
	{
		vars->args->limiteat += atoi(argv[5]) + 1;
		vars->args->param = 6;
	}
	vars->cutl = malloc(sizeof(pthread_mutex_t) * vars->args->philos);
	if (!vars->cutl)
		return (errors("\033[1;31mcutl malloc failed!\n"));
	while (i < vars->args->philos)
		pthread_mutex_init(&(vars->cutl[i++]), NULL);
	pthread_mutex_init(&(vars->writing), NULL);
	pthread_mutex_init(&(vars->dead), NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	*vars;
	int		i;

	i = -1;
	usleep (1000);
	if (comprove(argv, argc) != 1)
		return (0);
	vars = (t_vars *)malloc(sizeof(t_vars));
	if (!vars)
		return (errors("\033[1;31mvars malloc failed!\n"));
	if (initargs(vars, argc, argv, i) != 0)
		return (0);
	if (initphilos(vars) != 0)
		return (0);
	if (!start(vars, i))
		return (0);
	free_all(&vars->philo[0]);
	return (0);
}
