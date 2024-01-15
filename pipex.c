/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elchakir <elchakir@student.41.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 20:28:34 by elchakir          #+#    #+#             */
/*   Updated: 2024/01/15 18:59:16 by elchakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_arg(void)
{
	char	*error1;
	char	*error2;

	error1 = "\033[1;31m!! Invalid arguments.!!\n\033[0m\n";
	error2 = "\033[1;31mUsage: ./pipex infile cmd1 cmd2 outfile\n\033[0m\n";
	write(2, error1, ft_strlen(error1));
	write(2, error2, ft_strlen(error2));
	exit(EXIT_FAILURE);
}

void	ft_clear_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	open_file(char **av, int ac, int *out)
{
	int	in;
	int	i;

	i = 2;
	*out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	in = open(av[1], O_RDONLY, 0777);
	if (in == -1 || *out == -1)
		perror("file descriptor error !");
	dup2(in, 0);
	close(in);
}

int	main(int ac, char **av, char **ev)
{
	int	out;
	int	i;
	int	status;

	if (ac != 5)
		error_arg();
	i = 2;
	open_file(av, ac, &out);
	while (i <= ac - 2)
	{
		do_pipe(&av[i], ev, (i == ac - 2), out);
		i++;
	}
	while (wait(&status) > 0)
		;
	return (exit(status), 0);
}
