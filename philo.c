/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecsong <yecsong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 01:01:07 by yecsong           #+#    #+#             */
/*   Updated: 2022/12/09 14:56:52 by yecsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int		sign;
	size_t	i;
	size_t	num;

	num = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (sign * num);
}

t_arg	*init_arg(char **argv)
{
	t_arg	*arg;
	int		i;

	i = 0;
	arg = (t_arg*)malloc(sizeof(t_arg));
	arg->philo_idx = 0;
	arg->number_of_philo = ft_atoi(argv[1]);
	arg->time_to_die = ft_atoi(argv[2]);
	arg->time_to_eat = ft_atoi(argv[3]);
	arg->time_to_sleep = ft_atoi(argv[4]);
	arg->start = NULL;
	arg->fork = (int *)malloc(sizeof(int) * arg->number_of_philo);
	arg->mutex = (pthread_mutex_t*)malloc \
				 (sizeof (pthread_mutex_t) * arg->number_of_philo);
	arg->time_mutex = (pthread_mutex_t*)malloc \
					  (sizeof(pthread_mutex_t) * arg->number_of_philo);
	arg->start = (struct timeval *)malloc(sizeof(struct timeval));
	arg->start->tv_sec = 0;
	arg->start->tv_usec = 0;
	while (i < arg->number_of_philo)
	{
		pthread_mutex_init(&arg->mutex[i], NULL);
		pthread_mutex_init(&arg->time_mutex[i], NULL);
		arg->fork[i] = 0;
		i++;
	}
	pthread_mutex_init(&arg->philo_mutex, NULL);
	// ㅇㅏ직 쓰레드 만들어지기 전
	return (arg);
}

void	print_time_stamp(t_arg *arg, int idx, int flag)
{
	long 	now_ms;
	long 	start;
	long	diff;
	gettimeofday(&arg->philo[idx].now, NULL);
	now_ms = arg->philo[idx].now.tv_sec * 1000 + arg->philo[idx].now.tv_usec / 1000;
	start = arg->start->tv_sec * 1000 +  arg->start->tv_usec / 1000;
	diff = now_ms - start;
	pthread_mutex_lock(&arg->philo_mutex);
	if (!arg->is_dead)
	{
		if (flag == PICK_UP_FORK)
			printf("%ld %d has taken a fork\n", diff ,idx);
		else if (flag == IS_EATING)
			printf("%ld %d is eating\n", diff ,idx);
		else if (flag == IS_SLEEPING)
			printf("%ld %d is sleeping\n", diff ,idx);
		else if (flag == IS_THINKING)
			printf("%ld %d is thinking\n", diff ,idx);
	}
	pthread_mutex_unlock(&arg->philo_mutex);
}

void	precision_sleep(int time)
{
	struct timeval	now;
	long			now_ms;
	long			start;

	gettimeofday(&now, NULL);
	usleep(time * 900);
	start =  now.tv_sec * 1000 + now.tv_usec / 1000;
	now_ms = now.tv_sec * 1000 + now.tv_usec / 1000;
	while (now_ms < start + time)
	{
		gettimeofday(&now, NULL);
		now_ms = now.tv_sec * 1000 + now.tv_usec / 1000;
	}
}

void	*handler(void *arg)
{
	t_arg	*tmp; 
	int		idx;

	tmp = (t_arg *)arg;
	pthread_mutex_lock(&tmp->philo_mutex);
	idx	= tmp->philo_idx;
	tmp->philo_idx++;
	pthread_mutex_unlock(&tmp->philo_mutex);
	while (1)
	{
		pthread_mutex_lock(&tmp->philo_mutex);
		if (tmp->philo_idx == tmp->number_of_philo)
		{
			if (tmp->start->tv_sec == 0 && tmp->start->tv_usec == 0 )
				gettimeofday(tmp->start, NULL);
			pthread_mutex_unlock(&tmp->philo_mutex);
			break ;
		}
		pthread_mutex_unlock(&tmp->philo_mutex);
	}
	int i;

	i = 0;
	while (i < tmp->number_of_philo)
	{
		pthread_mutex_lock(&tmp->time_mutex[idx]);
		tmp->philo[idx].last_eat.tv_sec = tmp->start->tv_sec;
		tmp->philo[idx].last_eat.tv_usec = tmp->start->tv_usec;
		pthread_mutex_unlock(&tmp->time_mutex[idx]);
		i++;
	}
	if (idx & 1)
		usleep(tmp->time_to_eat * 200);
	// pick up fork
	tmp->philo[idx].left = (tmp->number_of_philo + idx - 1) % tmp->number_of_philo;
	tmp->philo[idx].right = idx;
	while (1)
	{
		if (idx == 0)
			usleep(100);
		pthread_mutex_lock(&tmp->mutex[tmp->philo[idx].right]);
		if (tmp->fork[idx] == 0)
		{
		tmp->fork[idx] = 1;
		//print_time_stamp(tmp, idx, PICK_UP_FORK);
		}
		pthread_mutex_lock(&tmp->mutex[tmp->philo[idx].left]);
		if (tmp->fork[(tmp->number_of_philo + idx - 1) % tmp->number_of_philo]== 0)
		{
			tmp->fork[(tmp->number_of_philo + idx - 1) % tmp->number_of_philo] = 1;
		//	print_time_stamp(tmp, idx, PICK_UP_FORK);
		}
		// eating
		if (tmp->fork[idx] == 1 && tmp->fork[(tmp->number_of_philo + idx - 1) % tmp->number_of_philo] == 1)
		{
			print_time_stamp(tmp, idx, IS_EATING);
			precision_sleep(tmp->time_to_eat);
			pthread_mutex_lock(&tmp->time_mutex[idx]);
			gettimeofday(&tmp->philo[idx].last_eat, NULL);
			pthread_mutex_unlock(&tmp->time_mutex[idx]);
			tmp->fork[tmp->philo[idx].left] = 0;
			tmp->fork[tmp->philo[idx].right] = 0;
		}
		// fork mutex unlock
		pthread_mutex_unlock(&tmp->mutex[tmp->philo[idx].left]);
		pthread_mutex_unlock(&tmp->mutex[tmp->philo[idx].right]);
		// sleep 
		print_time_stamp(tmp, idx, IS_SLEEPING);
		precision_sleep(tmp->time_to_sleep);
		// think
		//print_time_stamp(tmp, idx, IS_THINKING);
		pthread_mutex_lock(&tmp->philo_mutex);
		if (tmp->is_dead == 1)
			break;
		pthread_mutex_unlock(&tmp->philo_mutex);
		// check_dead
	}
	pthread_mutex_unlock(&tmp->philo_mutex);
	return (NULL);
}

int	monitor_thread(t_arg *arg)
{
	int 			i;
	int				is_dead;
	struct timeval	now;
	long			time;

	i = 0;
	is_dead = 0;
	while (i < arg->number_of_philo)
	{
		gettimeofday(&now, NULL);
		pthread_mutex_lock(&arg->time_mutex[i]);
		if ((time = ((now.tv_sec - arg->philo[i].last_eat.tv_sec) * 1000 \
				+ (now.tv_usec - arg->philo[i].last_eat.tv_usec) / 1000) \
				> arg->time_to_die))
		{
			is_dead = 1;
			break;
		}
		pthread_mutex_unlock(&arg->time_mutex[i]);
		//printf("time = %d\n", time);
		i++;
	}
	if (is_dead)
	{
		pthread_mutex_unlock(&arg->time_mutex[i]);
		pthread_mutex_lock(&arg->philo_mutex);
		arg->is_dead = 1;
		pthread_mutex_unlock(&arg->philo_mutex);
		printf("%ld %d died\n", (now.tv_sec - arg->start->tv_sec) * 1000 \
				+ (now.tv_usec - arg->start->tv_usec) / 1000, i);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_arg		*arg;
	t_philo		*philo;
	pthread_t	*tid;
	int			i;

	if (!(argc == 6 || argc == 5))
		return (-1);
	arg = init_arg(argv);
	philo = (t_philo *)malloc(sizeof(t_philo) * arg->number_of_philo);
	i = 0;
	while (i < arg->number_of_philo)
	{
		gettimeofday(&philo[i].last_eat, NULL);
		i++;
	}
	arg->philo = philo;
	i = 0;
	if (argc == 6)		
		while (i < arg->number_of_philo)
			arg->philo[i++].eat_cnt = ft_atoi(argv[5]);
	i = 0;
	tid = (pthread_t *)malloc(sizeof(pthread_t) * arg->number_of_philo);
	while (i < arg->number_of_philo)
	{
		if (pthread_create(tid + i, NULL, handler, (void *)arg))
			return (-1);
		i++;
	}
	
	while (1)
	{
		
		if (monitor_thread(arg))
			break ;
	}
	
	i = 0;
	while (i < arg->number_of_philo)
		pthread_join(tid[i++], NULL);
	i = 0;
	while (i < arg->number_of_philo)
		pthread_mutex_destroy(&arg->mutex[i++]);
	pthread_mutex_destroy(&arg->philo_mutex);
}