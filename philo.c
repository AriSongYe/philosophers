/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecsong <yecsong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 01:01:07 by yecsong           #+#    #+#             */
/*   Updated: 2022/12/05 12:57:02 by yecsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_arg	*init_arg(t_time_info *info)
{
	t_arg	*new;
	int		*state;
	int		i;
	
	new = (t_arg *)malloc(sizeof(t_arg));
	state = (int *)malloc(sizeof(int) * info->number_of_philo);
	i = 0;
	while (i < info->number_of_philo)
		state[i++] = SLEEP;
	new->state = state;
	new->info = info;
	new->index = 0;
	return (new);
}

t_time_info	*init_info(char **argv)
{
	t_time_info	*info;

	info = (t_time_info *)malloc(sizeof(t_time_info));
	info->number_of_philo = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	info->must_eat_time = ft_atoi(argv[5]);
	return (info);
}

void	eating(t_arg **arg)
{
	printf("%d: Now, I'm eating\n", (*arg)->index);
	usleep((*arg)->info->time_to_eat);
}

void	sleeping(t_arg **arg)
{
	printf("%d\n: Now, I'm sleeping\n", (*arg)->index);
	usleep((*arg)->info->time_to_sleep);
}

int	left_index(t_arg **arg)
{
	return (((*arg)->index + (*arg)->info->number_of_philo - 1) \
			% (*arg)->info->number_of_philo);
}

int	right_index(t_arg **arg)
{
//	return (((*arg)->index + 1) % (*arg)->info->number_of_philo);
	return ((*arg)->index);
}

void	test(t_arg **arg ,int index)
{
	if ((*arg)->state[index] == HUNGRY && \
			(*arg)->state[left_index(arg)] != EATING && \
			(*arg)->state[right_index(arg)] != EATING)
		(*arg)->state[index] = EATING;
}

void	pick_up(t_arg **arg)
{
	pthread_mutex_lock(&(*arg)->info->mutex);
	(*arg)->state[(*arg)->index] = HUNGRY;
	test(arg, (*arg)->index);
	pthread_mutex_unlock(&(*arg)->info->mutex);
}

void	put_down(t_arg **arg)
{
	pthread_mutex_lock(&(*arg)->info->mutex);
	(*arg)->state[(*arg)->index] = SLEEP;
	test(arg, left_index(arg));
	test(arg, right_index(arg));
	pthread_mutex_unlock(&(*arg)->info->mutex);
}

void	*pthread_handler(void *param)
{
	t_arg	*arg;
	
	
	arg = (t_arg *)param;
	while (1)
	{
		printf("index =%d\n", arg->index);
		sleeping(&arg);
		pick_up(&arg);
		eating(&arg);
		put_down(&arg);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_time_info	*info;
	pthread_t	*tid;
	t_arg		*arg;
	int			i;
	int			tid_num;

	(void)argc;
//	if (argc != 6)
//		return (-1);
	// init region //
	info = init_info(argv);
	gettimeofday(&info->start, NULL);
	arg = init_arg(info);
	pthread_mutex_init(&info->mutex, NULL);
	tid = (pthread_t *)malloc(sizeof(pthread_t) * info->number_of_philo + 1);
	i = 0;
	arg->index = i;
	// practice thread //
	while (i < info->number_of_philo)
	{
		arg->index = i;
		tid_num = pthread_create(tid + i++, NULL, pthread_handler, arg);
		if (tid_num < 0)
			return (-1);
	}
	i = 0;
	// free region // 
	while (i < info->number_of_philo)
		pthread_join(tid[i++], NULL);
	pthread_mutex_destroy(&info->mutex);
	free(arg->state);
	free(arg);
	free(info);
}
