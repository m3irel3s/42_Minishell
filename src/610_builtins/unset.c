/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeirele <jmeirele@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:15:01 by jmeirele          #+#    #+#             */
/*   Updated: 2025/02/17 16:19:08 by jmeirele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// check if the var exists

static void	ft_remove_var_update_env(t_shell *shell, char *var);
void	ft_unset(t_shell *shell)
{
	t_token	*curr;
	
	curr = shell->tokens;
	if (!curr->next)
		return ;
	while (curr->next)
	{
		curr = curr->next;
		if (!(ft_get_var_index(curr->value, shell->env_cpy) == -1))
			ft_remove_var_update_env(shell, curr->value);
		else
			continue;
	}
}

static void	ft_remove_var_update_env(t_shell *shell, char *var)
{
	char	**new_env;
	int		var_index;
	int		i;
	int		j;

	i = 0;
	j = 0;
	var_index = ft_get_var_index(var, shell->env_cpy);
	new_env = ft_safe_malloc(sizeof(char *) * (ft_get_env_size(shell) - 1));
	while (shell->env_cpy[i])
	{
		if (i != var_index)
			new_env[j++] = ft_strdup(shell->env_cpy[i]);
		i++;
	}
	new_env[j] = NULL;
	ft_free_arr(shell->env_cpy);
	shell->env_cpy = ft_duplicate_env(new_env);
}