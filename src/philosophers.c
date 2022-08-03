/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: develoi89 <develoi89@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:05:22 by ealonso-          #+#    #+#             */
/*   Updated: 2022/08/03 13:15:32 by develoi89        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/philosophers.h"

static int	initphilos(t_vars *vars, int argc)
{
	int	i;

	i = 0;
	vars->philo = malloc(sizeof(t_philo) * vars->args->philos);
	if (!vars->philo)
		return (0);
	while (vars->args->philos - i != 0)
	{
		vars->philo[i].phnum = i + 1;
		vars->philo[i].right = i;
		if (i != 30)
			vars->philo[i].left = i + 1;
		else
			vars->philo[i].left = 0;
		if (argc == 6)
			vars->philo[i].limiteat = vars->args->limiteat;
		i++;
	}
	return (1);
}

static void	initargs(t_vars *vars, int argc, char **argv)
{
	int i;

	i = 0;
	vars->args = malloc(sizeof(t_args));
	vars->args->philos = atoi(argv[1]);
	vars->args->tte = atoi(argv[3]);
	vars->args->ttd = atoi(argv[2]);
	vars->args->tts = atoi(argv[4]);
	if (argc == 6)
		vars->args->limiteat = atoi(argv[5]);
	pthread_mutex_init(&vars->writing, NULL);
	pthread_mutex_init(&vars->dead, NULL);
	vars->cutl = malloc(sizeof(pthread_mutex_t) * vars->args->philos);
	while (i < vars->args->philos)
		pthread_mutex_init(&vars->cutl[i++], NULL);
}

int	main(int argc, char **argv)
{
	t_vars	*vars;

	if (comprove(argv, argc) != 1)
		return (0);
	vars = (t_vars *)malloc(sizeof(t_vars));
	if (!vars)
		return (errors("\033[1;31mvars malloc failed!\n"));
	initargs(vars, argc, argv);
	initphilos(vars, argc);
	free_all(vars);
	return (0);
}
