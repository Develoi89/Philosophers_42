/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealonso- <ealonso-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:05:22 by ealonso-          #+#    #+#             */
/*   Updated: 2022/08/22 17:02:44 by ealonso-         ###   ########.fr       */
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
		if (i != vars->args->philos - 1)
			vars->philo[i].left = i + 1;
		else
			vars->philo[i].left = 0;
		if (argc == 6)
			vars->philo[i].limiteat = vars->args->limiteat;
		printf("For philo num %d, cutl left is %d and right is %d\n",
			vars->philo[i].phnum, vars->philo[i].right, vars->philo[i].left);
		i++;
	}
	return (1);
}

static int	initargs(t_vars *vars, int argc, char **argv)
{
	int	i;

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
	vars->cutl = malloc(sizeof(pthread_mutex_t) * vars->args->philos);
	if (!vars->cutl)
		return (errors("\033[1;31mcutl malloc failed!\n"));
	while (i < vars->args->philos)
		pthread_mutex_init(&vars->cutl[i++], NULL);
	pthread_mutex_init(&vars->writing, NULL);
	pthread_mutex_init(&vars->dead, NULL);
	printf("philos:%d\ntime to eat:%d\ntime to die:%d\ntime to sleep:%d\n",
		vars->args->philos, vars->args->tte, vars->args->ttd, vars->args->tts);
	return (0);
}

static void	*routine(void *var)
{
	t_vars	*vars;
	int		id;
	pthread_mutex_t p;

	pthread_mutex_init(&p, NULL);
	vars = (t_vars *)var;
	id = vars->id;
	// if (id % 2 == 0)
	// 	time_sleep(200);
	// printf("cubierto izq:%d", vars->philo[id].left);
	// printf("cubierto dcha:%d", vars->philo[id].right);
	// pthread_mutex_lock(&vars->cutl[vars->philo[id].left]);
	// pthread_mutex_lock(&vars->cutl[vars->philo[id].right]);
	pthread_mutex_lock(&p);
	printf("hola");
	pthread_mutex_unlock(&p);
	// pthread_mutex_unlock(&vars->cutl[vars->philo[id].left]);
	// pthread_mutex_unlock(&vars->cutl[vars->philo[id].right]);
	printf("hola");
	return (NULL);
}

static int	start(t_vars *vars)
{
	int			i;
	pthread_t	*threads;

	i = 0;
	threads = (pthread_t *)malloc(sizeof(pthread_t) * vars->args->philos);
	if (!threads)
		return (errors("\033[1;31mthreads malloc failed!\n"));
	while (i < vars->args->philos)
	{
		vars->id = i;
		pthread_create(&threads[i], NULL, &routine, vars);
		sleep(100);
		i++;
	}
	i = 0;
	while (i < vars->args->philos)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	// free (threads);
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
