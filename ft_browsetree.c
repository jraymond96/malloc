/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_browsetree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 15:28:31 by jraymond          #+#    #+#             */
/*   Updated: 2019/11/20 11:16:01 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_browsetree(t_btree *root, void (*dothings)(void *))
{
	if (!root || !dothings)
		return ;
	if (root->left)
		ft_browsetree(root->left, dothings);
	dothings(root->ptrdata);
	if (root->right)
		ft_browsetree(root->right, dothings);
}

void	ft_revbrowsetree(t_btree *root, void (*dothings)(void *))
{
	if (!root || !dothings)
		return ;
	if (root->right)
		ft_revbrowsetree(root->right, dothings);
	dothings(root->ptrdata);
	if (root->left)
		ft_revbrowsetree(root->left, dothings);
}
