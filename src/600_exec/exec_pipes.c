/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:43:03 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/20 17:21:14 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


// cmd1 writes to fd[1] of Pipe 1.
// cmd2 reads from fd[0] of Pipe 1 and writes to fd[3] of Pipe 2.
// cmd3 reads from fd[2] of Pipe 2.

static int	*ft_allocate_and_create_pipes(t_token *tokens, int *pipes);
static int	ft_count_pipes(t_token *tokens);

void ft_handle_pipes(t_shell *shell)
{
	int	*pipes;

	pipes = NULL;
	pipes = ft_allocate_and_create_pipes(shell->tokens, pipes);
	for (int i = 0; pipes[i]; i++)
	{
		printf("ola\n");
	}
	
}

static int	*ft_allocate_and_create_pipes(t_token *tokens, int *pipes)
{
	int	i;
	int	num_pipes;

	num_pipes = ft_count_pipes(tokens);
	pipes = ft_safe_malloc(sizeof(int) * 2 * num_pipes);
	i = 0;
	while (i < num_pipes)
	{
		if (pipe(&pipes[i * 2]) == -1)
		{
			//error creating pipe
			ft_printf(2, "minishell: error creating pipe\n");
			return NULL;
		}
		i++;
	}
	return (pipes);
}

static int	ft_count_pipes(t_token *tokens)
{
	int counter;

	counter = 0;
	while (tokens)
	{
		if (tokens->type == PIPE)
			counter++;
		tokens = tokens->next;
	}
	return (counter);
}



