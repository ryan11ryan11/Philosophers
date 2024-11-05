/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:19:16 by junhhong          #+#    #+#             */
/*   Updated: 2024/09/30 10:34:56 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	fork_release(t_args *args, int philo_index)
{
	pthread_mutex_unlock(args->philo_struct[philo_index].r_fork);
	pthread_mutex_unlock(args->philo_struct[philo_index].l_fork);
}

void	fork_take(t_args *args, int philo_index)
{
	pthread_mutex_lock(args->philo_struct[philo_index].r_fork);
	pthread_mutex_lock(args->philo_struct[philo_index].l_fork);
	announce(args, philo_index, TAKE_FORK);
	pthread_mutex_lock(&args->lasteat_lock);
	args->philo_struct[philo_index].last_eat = get_time();
	pthread_mutex_unlock(&args->lasteat_lock);
	announce(args, philo_index, EATING);
	if (args->not >= 0)
		args->philo_struct[philo_index].meals ++ ;
	usleep(args->tte * 1000);
}

void	thinking(t_args *args, int philo_index)
{
	announce(args, philo_index, THINKING);
}

void	sleeping(t_args *args, int philo_index)
{
	announce(args, philo_index, SLEEPING);
	usleep (args->tts * 1000);
}
