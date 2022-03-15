/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odomenic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 19:14:36 by odomenic          #+#    #+#             */
/*   Updated: 2021/09/01 20:12:25 by odomenic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <sys/types.h>
# include <stdlib.h>
# include <semaphore.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <signal.h>

/*typedef struct s_philo
{
	struct s_config	*conf;
	pid_t			pid;
	int				i;
	unsigned long	last_eat;
	int				eat_times;
	sem_t			*eating;
}				t_philo;*/

typedef struct s_config
{
	int				philo_num;
	pid_t			*philos;
	sem_t			*forks;
	sem_t			*to_write;
	sem_t			*death;
	sem_t			*eating;
	unsigned long	time_die;
	unsigned long	time_eat;
	unsigned long	time_sleep;
	int				eat_times;
	unsigned long	start_time;
	unsigned long	last_eat;
	int				phil_eat_times;
	int				check_end;
	int				i;
}				t_config;

int				ft_atoi(const char *str);
int				ft_isdigit(int c);
size_t			ft_strlen(char *str);
unsigned long	get_time(void);
void			new_printf(t_config *conf, char *str);
int				create_processes(t_config *config);
void			ft_usleep(int time);

#endif
