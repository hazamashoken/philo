/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_define.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 12:21:35 by tliangso          #+#    #+#             */
/*   Updated: 2022/11/08 23:18:24 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_DEFINE_H
# define PHILO_DEFINE_H

# define RESET "\e[0m"
# define PINK "\e[0;38;5;199m"
# define RED	"\e[1;31m"
# define GREEN	"\e[1;32m"
# define YELLOW	"\e[1;33m"
# define BLUE	"\e[1;34m"
# define WHITE	"\e[1;37m"

# define TRUE 1
# define FALSE 0

# define HELP "last parameter is optional:\n\
./philo [num of philo] [time till death] [eating duration] \
[sleeping duration] {time for each philo to eat}\n"

# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define LEFT_FORK "has taken a fork"
# define RIGHT_FORK "has taken a fork"
# define DIED "died"

#endif
