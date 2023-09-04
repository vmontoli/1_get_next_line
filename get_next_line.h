/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmontoli <vmontoli@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 09:36:04 by vmontoli          #+#    #+#             */
/*   Updated: 2023/09/04 23:43:41 by vmontoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# if ~(~BUFFER_SIZE + 0) == 0 && ~(~BUFFER_SIZE + 1) == 1
#  undef BUFFER_SIZE
# endif

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
	bool					has_eof;
	size_t					size;
	bool					has_newline;
	size_t					newline_pos;
	struct s_buffer_node	*next;
}	t_buffer_node;

/***/
char			*get_next_line(int fd);
/***/

/**/

t_buffer_node	*new_buffer_node(int fd);

void			set_newline_pos(t_buffer_node *buff_node);

void			*free_buffer_list(t_buffer_node **buffer_list_ptr,
					bool maintain_last);

void			tidy_buff_list(t_buffer_node **buffer_list_ptr);

size_t			copy_buff_node_to_str(t_buffer_node *curr_buff_node, char *str);

char			*generate_result(t_buffer_node *buffer_list);

/*
char			*generate_empty_result(t_buffer_node *buffer_list);

void			fill_result_tidy_buff_list(char *result,
					t_buffer_node **buffer_list_ptr);
*/

#endif
