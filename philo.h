/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecsong <yecsong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 01:01:17 by yecsong           #+#    #+#             */
/*   Updated: 2022/12/09 16:59:22 by yecsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PICK_UP_FORK	0
# define IS_EATING		1
# define IS_SLEEPING	2
# define IS_THINKING	3
# define DIE			4

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				state;
	int				left;
	int				right;
	struct timeval	now;
	struct timeval	last_eat;
}	t_philo;

typedef struct s_arg
{
	int				philo_idx;
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				*fork;
	int				is_dead;
	int				eat_cnt;
	long			start;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	*time_mutex;
	pthread_mutex_t	*start_dead_mutex;
	t_philo			*philo;
}	t_arg;

int		valid_argv(int argc, char **argv);
int		ft_strlen(char *str);
int		ft_atoi(const char *str);
void	*ft_memset(void *dest, int value, size_t len);
void	*ft_calloc(size_t count, size_t size);

#endif
