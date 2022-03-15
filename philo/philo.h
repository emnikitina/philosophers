/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odomenic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 20:05:57 by odomenic          #+#    #+#             */
/*   Updated: 2021/08/31 20:42:43 by odomenic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <sys/types.h>
# include <stdlib.h>

typedef struct s_philo
{
	struct s_config	*conf;
	pthread_t		th;
	int				i;
	unsigned long	last_eat;
	int				eat_times;
	pthread_mutex_t	eating;
}				t_philo;

typedef struct s_config
{
	int				philo_num;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	to_write;
	pthread_mutex_t	death;
	unsigned long	time_die;
	unsigned long	time_eat;
	unsigned long	time_sleep;
	int				eat_times;
	unsigned long	start_time;
	int				check_end;
	int				all_done_eat;
}				t_config;

int				ft_atoi(const char *str);
int				ft_isdigit(int c);
size_t			ft_strlen(char *str);
unsigned long	get_time(void);
void			new_printf(t_philo *phil, char *str);
int				create_threads(t_config *config);
void			ft_usleep(int time);

#endif
