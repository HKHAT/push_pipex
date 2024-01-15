/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elchakir <elchakir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 19:14:04 by elchakir          #+#    #+#             */
/*   Updated: 2024/01/15 19:13:44 by elchakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <unistd.h>
# define BUFFER_SIZE 100000

void	error_p(char *error, int err);
void	error_arg(void);
char	*find_path(char *cmd, char **ev);
int		gnl(char **line);
void	ft_clear_tab(char **tab);
char	*build_executable_path(char *cmd, char *path);
void	exe(char **ev, char *av);
void	do_pipe(char **av, char **ev, int is_last, int out_fd);
void	here_doc(char *limiter, int ac);

#endif
