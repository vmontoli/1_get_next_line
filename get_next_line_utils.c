/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmontoli <vmontoli@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 09:44:42 by vmontoli          #+#    #+#             */
/*   Updated: 2023/08/21 19:22:53 by vmontoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	char	*res;

	i = count * size;
	res = (char *) malloc(i);
	if (res == NULL)
		return (NULL);
	while (i > 0)
		res[--i] = 0;
	return ((void *) res);
}

//TODO: explain
char	*find_new_line(char *start_str, char *end_str)
{
	char	*result;

	result = start_str;
	while (result != end_str)
	{
		if (*result == '\n')
			return (result);
		result++;
	}
	return (NULL);
}

char	*generate_result(t_buffer_list **buffer_list_ptr, char *newline_ptr)
{
	char			*result;
	char			*curr_result;
	ssize_t			len;
	t_buffer_list	*doing_buffer_l;

	len = 1;
	doing_buffer_l = *buffer_list_ptr;
	while (doing_buffer_l->next != NULL)
	{
		len += doing_buffer_l->end - doing_buffer_l->start + 1;
		doing_buffer_l = doing_buffer_l->next;
	}
	len += newline_ptr - doing_buffer_l->start + 1;
	result = (char *) malloc(len);
	if (result == NULL)
	{
		*buffer_list_ptr = NULL;
		return (NULL);
	}
	result[len - 1] = '\0';
	curr_result = result;
	doing_buffer_l = *buffer_list_ptr;
	while (doing_buffer_l->next != NULL)
	{
		ft_strncpy(curr_result, doing_buffer_l->start,
			doing_buffer_l->end - doing_buffer_l->start + 1);
		curr_result += doing_buffer_l->end - doing_buffer_l->start + 1;
		doing_buffer_l = doing_buffer_l->next;
	}
	ft_strncpy(curr_result, doing_buffer_l->start,
		newline_ptr - doing_buffer_l->start + 1);
}
