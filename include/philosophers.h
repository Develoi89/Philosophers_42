/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: develoi89 <develoi89@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:08:33 by ealonso-          #+#    #+#             */
/*   Updated: 2022/09/22 10:55:31 by develoi89        ###   ########.fr       */
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
	t_args			*args;
	t_philo			*philo;
	pthread_t		*threads;
	long long int	start_time;
	pthread_mutex_t	dead;
	pthread_mutex_t	*cutl;
	pthread_mutex_t	writing;
}	t_vars;

int				errors(char *s);
int				comprove(char **argv, int argc);

void			time_sleep(int i);
void			*routine(void *var);
void			free_all(t_vars *vars);
void			printing(char *sms, t_vars *vars, int id);

long long int	get_time(void);
long long int	ft_atoi(const char *str);

#endif