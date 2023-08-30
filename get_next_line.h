/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmontoli <vmontoli@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 09:36:04 by vmontoli          #+#    #+#             */
/*   Updated: 2023/08/30 08:42:53 by vmontoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# include <stddef.h>		//NULL, size_t
# include <stdbool.h>		//bool, true, false

# include <stdlib.h>		//malloc(), free()
# include <unistd.h>		//read()

typedef struct s_buffer_node
{
	char					buffer[BUFFER_SIZE];
	char					*start;
	ssize_t					size;
	struct s_buffer_node	*next;
}	t_buffer_node;

/***/
char			*get_next_line(int fd);
/***/

/**/

t_buffer_node	*new_buffer_node(int fd);

ssize_t			find_newline_pos(t_buffer_node *buff_node);

void			*free_buffer_list(t_buffer_node **buffer_list_ptr,
					bool maintain_last);

char			*generate_result(t_buffer_node **buffer_list_ptr,
					ssize_t newline_pos);

#endif
