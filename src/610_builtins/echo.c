/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:22:57 by jmeirele          #+#    #+#             */
/*   Updated: 2025/03/14 17:37:11 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static bool	ft_echo_handle_flag(char *str);
static void	ft_echo_print_args(t_token *curr);

/**
 * Executes the echo command in the shell with options to handle flags.
 * Iterates over the tokens linked list to check for the '-n' flag,
 * which suppresses the trailing newline. Prints the arguments provided
 * to the echo command and adds a newline at the end unless the '-n' flag
 * is present. Sets the global exit status to success upon completion.
 *
 * @param shell A pointer to the shell structure, which contains a linked list
 *              of tokens representing parsed command arguments.
 */
void	ft_echo(t_shell *shell)
{
	t_token	*curr;
	bool	add_new_line;

	add_new_line = true;
	curr = shell->tokens->next;
	if (!curr)
	{
		ft_printf(STDOUT_FILENO, "\n");
		g_exit_status = EXIT_SUCCESS;
		return ;
	}
	while (curr && ft_echo_handle_flag(curr->val.value))
	{
		add_new_line = false;
		curr = curr->next;
	}
	ft_echo_print_args(curr);
	if (add_new_line)
		ft_printf(STDOUT_FILENO, "\n");
	g_exit_status = EXIT_SUCCESS;
}

/**
 * Prints all the arguments provided to the echo command. Iterates over the
 * provided tokens and prints their values. If the next token is a WORD, a
 * space is printed in between.
 *
 * @param curr A pointer to the current token in the linked list.
 */
static void	ft_echo_print_args(t_token *curr)
{
	while (curr)
	{
		ft_printf(STDOUT_FILENO, "%s", curr->val.value);
		curr = curr->next;
		if (curr && curr->type == WORD)
			ft_printf(STDOUT_FILENO, " ");
		else
			break ;
	}
}

/**
 * Checks if the provided string is a valid flag for the echo command.
 * The only valid flag is '-n', so this function checks if the first
 * character is '-' and the second character is 'n'. It then checks if
 * there are any other characters after 'n' and if they are all 'n'. If
 * the string passes all these checks, this function returns true, else
 * it returns false.
 *
 * @param str A pointer to the string to check.
 *
 * @return True if the string is a valid flag, false otherwise.
 */
static bool	ft_echo_handle_flag(char *str)
{
	int		i;

	i = 0;
	if (str[0] != '-' || str[1] != 'n')
		return (false);
	i = 2;
	while (str[i] == 'n')
		i++;
	return (str[i] == '\0');
}
