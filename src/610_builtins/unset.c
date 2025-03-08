/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:15:01 by jmeirele          #+#    #+#             */
/*   Updated: 2025/03/08 22:46:37 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_status	ft_remove_var(t_shell *shell, char **new_env, int var_index);
static t_status	ft_remove_var_update_env(t_shell *shell, char *var);
static t_status	ft_is_valid_var_name(char *var);

void	ft_unset(t_shell *shell)
{
	t_token	*curr;

	curr = shell->tokens;
	if (!curr->next)
		return ;
	while (curr->next)
	{
		curr = curr->next;
		if (ft_is_valid_var_name(curr->val.value) == ERROR)
			g.g_exit_status = EXIT_SUCCESS;
		else if (ft_get_var_index(curr->val.value, shell->env_cpy) != -1)
			if (ft_remove_var_update_env(shell, curr->val.value) == ERROR)
				g.g_exit_status = EXIT_SUCCESS;
	}
	g.g_exit_status = EXIT_SUCCESS;
}

static t_status	ft_remove_var_update_env(t_shell *shell, char *var)
{
	char	**new_env;
	int		var_index;

	var_index = ft_get_var_index(var, shell->env_cpy);
	new_env = ft_safe_calloc(sizeof(char *) * (ft_get_env_size(shell)));
	if (!new_env)
		return (ERROR);
	ft_remove_var(shell, new_env, var_index);
	ft_free_arr(shell->env_cpy);
	shell->env_cpy = ft_duplicate_env(new_env);
	ft_free_arr(new_env);
	return (SUCCESS);
}

static t_status	ft_remove_var(t_shell *shell, char **new_env, int var_index)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (shell->env_cpy[i])
	{
		if (i != var_index)
		{
			new_env[j] = ft_safe_strdup(shell->env_cpy[i]);
			if (!new_env[j++])
			{
				ft_free_arr(new_env);
				return (ERROR);
			}
		}
		i++;
	}
	new_env[j] = NULL;
	return (SUCCESS);
}

static t_status	ft_is_valid_var_name(char *var)
{
	int	i;

	if (!var || !*var || ft_isdigit(*var))
		return (ERROR);
	i = 0;
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}
