/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprikhod <dprikhod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 11:52:33 by dprikhod          #+#    #+#             */
/*   Updated: 2025/08/19 16:49:08 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
# Description:
Allocates memory (using malloc(3)) and returns a new node. The ’content’ member 
variable is initialized with the given parameter ’content’.
The variable ’next’ is initialized to NULL.

# Parameters:
content: The content to store in the new node.

# Return value:
A pointer to the new node.
*/
t_list	*ft_lstnew(void *content)
{
	t_list	*list;

	list = (t_list *)malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->content = content;
	list->next = NULL;
	return (list);
}

/*
# Description:
Adds the node ’new’ at the beginning of the list.

# Parameters:
lst: The address of a pointer to the first node of a list.
new: The address of a pointer to the node to be added.

# Return value:
None
*/
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

/*
# description:
returns the last node of the list.

# parameters:
lst: the beggining of the list.

# return value:
last node of the list.
*/
t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

/*
# Description:
Adds the node ’new’ at the end of the list.

# Parameters:
lst: The address of a pointer to the first node of
a list.
new: The address of a pointer to the node to be
added.

# Return value:
None
*/
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
}
