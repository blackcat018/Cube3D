/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czghoumi <czghoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 23:44:56 by czghoumi          #+#    #+#             */
/*   Updated: 2024/11/10 01:19:49 by czghoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*s;

	if (lst == NULL || del == NULL)
		return ;
	while (*lst != NULL)
	{
		s = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = s;
	}
	*lst = NULL;
}
