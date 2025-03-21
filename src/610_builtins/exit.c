/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:22:55 by jmeirele          #+#    #+#             */
/*   Updated: 2025/03/16 21:55:32 by meferraz         ###   ########.fr       */
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
	if (!shell->are_pipes)
		write(STDOUT_FILENO, "exit\n", 5);
	if (!curr || !curr->next)
		return (ft_cleanup_w_env(shell), exit(g_exit_status));
	if (ft_valid_number(curr->next->val.value) == ERROR)
	{
		ft_print_error_w_arg(ERR_EXIT_NUM_REQ, curr->next->val.value,
			EXIT_MISUSE);
		ft_cleanup_w_env(shell);
		exit(g_exit_status);
	}
	if (curr->next->next)
	{
		ft_print_error(ERR_EXIT_TOO_MANY_ARGS);
		return ;
	}
	g_exit_status = ft_atoi(curr->next->val.value);
	if (g_exit_status > 255 || g_exit_status < 0)
		g_exit_status %= 256;
	ft_cleanup_w_env(shell);
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
	(void)shell;
	write(STDOUT_FILENO, "exit\n", 5);
	if (shell->env_cpy)
		ft_free_arr(shell->env_cpy);
	ft_free(shell->last_cwd);
	g_exit_status = EXIT_SUCCESS;
}

/**
 * ft_valid_number - Check if the given string is a valid number.
 * @str: The string to check.
 *
 * This function checks if the given string is a valid number by
 * verifying that it only contains digits. If the string starts with
 * a '+' or '-' character, it is ignored. If the string contains any
 * non-digit characters, ft_valid_number returns ERROR. Otherwise, it
 * returns SUCCESS.
 *
 * Return: SUCCESS if the string is a valid number, ERROR otherwise.
 */
static int	ft_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}
