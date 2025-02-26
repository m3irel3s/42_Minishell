/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:15:01 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/25 17:28:43 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_status	ft_remove_var_update_env(t_shell *shell, char *var);
static t_status	ft_is_valid_var_name(char *var);

void	ft_unset(t_shell *shell)
{
	t_token		*curr;
	t_status	status;

	curr = shell->tokens;
	status = SUCCESS;
	if (!curr->next)
		return ;
	while (curr->next)
	{
		curr = curr->next;
		if (ft_is_valid_var_name(curr->val.value) == ERROR)
		{
			//lacking error message
			status = EXIT_FAILURE;
		}
		else if (ft_get_var_index(curr->val.value, shell->env_cpy) != -1)
		{
			if (ft_remove_var_update_env(shell, curr->val.value) == ERROR)
				status = EXIT_FAILURE;
		}
	}
	g_exit_status = status;
}

static t_status	ft_remove_var_update_env(t_shell *shell, char *var)
{
	char	**new_env;
	int		var_index;
	int		i;
	int		j;

	i = 0;
	j = 0;
	var_index = ft_get_var_index(var, shell->env_cpy);
	new_env = ft_safe_malloc(sizeof(char *) * (ft_get_env_size(shell)));
	if (!new_env)
		return (ERROR);
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
	ft_free_arr(shell->env_cpy);
	shell->env_cpy = ft_duplicate_env(new_env);
	ft_free_arr(new_env);
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
