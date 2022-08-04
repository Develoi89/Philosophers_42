/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: develoi89 <develoi89@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:05:22 by ealonso-          #+#    #+#             */
/*   Updated: 2022/08/04 13:14:06 by develoi89        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/philosophers.h"

static int	initphilos(t_vars *vars, int argc)
{
	int	i;

	i = 0;
	vars->philo = malloc(sizeof(t_philo) * vars->args->philos);
	if (!vars->philo)
		return (errors("\033[1;31mphilos malloc failed!\n"));
	while (i < vars->args->philos)
	{
		vars->philo[i].phnum = i + 1;
		vars->philo[i].right = i;
		if (i != vars->args->philos)
			vars->philo[i].left = i + 1;
		else
			vars->philo[i].left = 0;
		if (argc == 6)
			vars->philo[i].limiteat = vars->args->limiteat;
		i++;
	}
	return (1);
}

static int	initargs(t_vars *vars, int argc, char **argv)
{
	int i;

	i = 0;
	vars->args = malloc(sizeof(t_args));
	if (!vars->args)
		return (errors("\033[1;31margs malloc failed!\n"));
	vars->args->philos = atoi(argv[1]);
	vars->args->tte = atoi(argv[3]);
	vars->args->ttd = atoi(argv[2]);
	vars->args->tts = atoi(argv[4]);
	if (argc == 6)
		vars->args->limiteat = atoi(argv[5]);
	pthread_mutex_init(&vars->writing, NULL);
	pthread_mutex_init(&vars->dead, NULL);
	vars->cutl = malloc(sizeof(pthread_mutex_t) * vars->args->philos);
	if (!vars->cutl)
		return (errors("\033[1;31mcutl malloc failed!\n"));
	while (i < vars->args->philos)
		pthread_mutex_init(&vars->cutl[i++], NULL);
	return (0);
}

static void	*routine(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	if (philo->phnum % 2 == 0)
		time_sleep(200);
	pthread_mutex_lock(&philo->vars->writing);
	printf("philo: %d\n", philo->phnum);
	pthread_mutex_unlock(&philo->vars->writing);
	return (NULL);
}

static int	start(t_vars *vars)
{
	int	i;
	pthread_t	*threads;

	i = - 1;
	threads = (pthread_t *)malloc(sizeof(pthread_t) * vars->args->philos);
	if (!threads)
		return (errors("\033[1;31mthreads malloc failed!\n"));
	while (++i < vars->args->philos)
		pthread_create(&threads[i], NULL, &routine, (void *)(&vars->philo[i]));
	i = - 1;
	while (++i < vars->args->philos)
		pthread_join(threads[i], NULL);
	free (threads);
	return (0);
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
	start(vars);
	free_all(vars);
	return (0);
}
