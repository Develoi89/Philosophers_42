/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealonso- <ealonso-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:08:33 by ealonso-          #+#    #+#             */
/*   Updated: 2022/10/05 16:30:27 by ealonso-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_args
{
	int				param;
	int				philos;
	int				limiteat;
	long long int	tte;
	long long int	ttd;
	long long int	tts;
}	t_args;

typedef struct s_philo
{
	int				left;
	int				phnum;
	int				right;
	int				meals;
	int				limiteat;
	long long int	tte;
	long long int	ttd;
	long long int	tts;
	long long int	time;
}	t_philo;

typedef struct s_vars
{	
	int				dd;
	int				id;
	int				init;
	int				done;
	t_args			*args;
	t_philo			*philo;
	pthread_t		*threads;
	long long int	start_time;
	pthread_mutex_t	dead;
	pthread_mutex_t	*cutl;
	pthread_mutex_t	writing;
}	t_vars;

typedef struct s_tmp
{
	t_vars	*vars;
	int		id;
}	t_tmp;

int				errors(char *s);
int				free_all(t_vars *vars);
int				comprove(char **argv, int argc);
int				printing(char *sms, t_vars *vars, int id);

void			time_sleep(int i);
void			*routine(void *var);
void			free_tmp(t_tmp **tmp, int i);

long long int	get_time(void);
long long int	ft_atoi(const char *str);

#endif
