/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bonus_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprikhod <dprikhod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:57:35 by dprikhod          #+#    #+#             */
/*   Updated: 2025/08/16 16:42:20 by dprikhod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
## Parameters
lst: The beginning of the list.
## Return value
The length of the list.
*/
int	ft_lstsize(t_list *lst)
{
	int	size;

	if (!lst)
		return (0);
	size = 1;
	while ((lst->next))
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

/*
Iterates through the list ’lst’ and applies the
function ’f’ to the content of each node.
## Parameters
lst: The address of a pointer to a node.
f: The address of the function to apply to each
node’s content.
## Return value
None
*/
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

/*
### Description:
Takes a node as parameter and frees its content
using the function ’del’. Free the node itself but
does NOT free the next node.

### Parameters:
lst: The node to free.
del: The address of the function used to delete
the content.

### Return value:
None
*/
void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst)
		return ;
	del(lst->content);
	free(lst);
	return ;
}

/*
Deletes and frees the given node and all its
successors, using the function ’del’ and free(3).
Finally, set the pointer to the list to NULL.
## Parameters
lst: The address of a pointer to a node.
del: The address of the function used to delete
the content of the node.
## Return value
None
*/
void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone(*lst, *del);
		*lst = tmp;
	}
	lst = NULL;
}

/*
Iterates through the list ’lst’, applies the
function ’f’ to each node’s content, and creates
a new list resulting of the successive applications
of the function ’f’. The ’del’ function is used to
delete the content of a node if needed.
## Parameters
lst: The address of a pointer to a node.
f: The address of the function applied to each
node’s content.
del: The address of the function used to delete a
node’s content if needed.
## Return value
The new list.
NULL if the allocation fails.
*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*last;

	if (!lst)
		return (NULL);
	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = f(lst->content);
	last = new;
	lst = lst->next;
	while (lst)
	{
		last->next = ft_lstnew(f(lst->content));
		if (!last)
			return (ft_lstclear(&new, del), NULL);
		lst = lst->next;
		last = last->next;
	}
	return (new);
}
