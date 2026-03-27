/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprikhod <dprikhod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 13:17:20 by dprikhod          #+#    #+#             */
/*   Updated: 2026/03/27 16:15:21 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Should create pipes for any here_doc needed.
 */
int	**prepare_pipes_for_here_doc(t_cmd *cmd)
{
	t_io	*list;
	int		len;
	int		i;
	int		*fd_here_doc[2];
	int		j;
	int		**ret;

	j = 0;
	i = 0;
	list = cmd->io_list;
	if (!list)
		return (NULL);
	len = ft_lstsize((t_list *)list);
	while (i < len)
	{
		if (list->type == TOKEN_HEREDOC)
		{
			pipe(*(fd_here_doc + j));
			j++;
		}
		list = list->next;
	}
	ret = malloc((sizeof(int[2])) * (j + 1));
	if (!ret)
		return (NULL);
	ft_memcpy(ret, fd_here_doc, sizeof(int[2]) * (j + 1));
	return (ret);
}

/*
* Write here_doc's 'line' to the pipe and close both ends of this pipe. Repeat 
* for every here_doc token.
*/
int	fill_here_doc(t_cmd *cmd, int *fd[2])
{
	t_io	*list;

	list = cmd->io_list;
	while (list->next)
	{
		if (list->type == TOKEN_HEREDOC)
		{
			close(*fd[0]);
			ft_putstr_fd(list->path, *fd[1]);
			close(*fd[1]);
			fd++;
		}
	}
	return (0);
}
