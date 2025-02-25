/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:22:55 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/25 17:18:55 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_valid_number(char *str);

/**
 * ft_exit - Exit the shell with the current exit status.
 * @shell: The t_shell structure containing the current exit status.
 *
 * This function will first call ft_handle_eof to handle any necessary
 * cleanup before exiting. Afterwards, it calls ft_cleanup to free any
 * dynamically allocated memory, and clears the history using rl_clear_history.
 * Finally, it calls exit with the current exit status.
 */
void	ft_exit(t_shell *shell)
{
	t_token	*curr;

	curr = shell->tokens;
	if (curr->next)
	{
		if (!curr->next->next && ft_valid_number(curr->next->value) == SUCCESS)
			g_exit_status = ft_atoi(curr->next->value);
		else if (curr->next->next)
			ft_print_error(ERR_EXIT_TOO_MANY_ARGS);
	}
	if (g_exit_status > 255 || g_exit_status < 0)
		g_exit_status %= 256;
	if (!curr->next)
		ft_handle_eof(shell);
	ft_cleanup(shell);
	rl_clear_history();
	exit(g_exit_status);
}

/**
 * ft_handle_eof - Handle an end-of-file event.
 * @shell: The t_shell structure containing the shell's exit status.
 *
 * This function will print "exit\n" to the standard output, free the
 * dynamically allocated memory for the shell's environment variables,
 * and set the shell's exit status to EXIT_SUCCESS.
 */
void	ft_handle_eof(t_shell *shell)
{
	write(STDOUT_FILENO, "exit\n", 5);
	if (shell->env_cpy)
		ft_free_arr(shell->env_cpy);
	g_exit_status = EXIT_SUCCESS;
}

static int	ft_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (ft_print_error_w_arg(ERR_EXIT_NUM_REQ, str), ERROR);
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (ft_print_error_w_arg(ERR_EXIT_NUM_REQ, str), ERROR);
		i++;
	}
	return (SUCCESS);
}
