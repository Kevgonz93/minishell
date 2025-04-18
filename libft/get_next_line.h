/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 10:30:29 by akwadran          #+#    #+#             */
/*   Updated: 2025/02/12 20:42:51 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H 
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
# include <stdlib.h>
# include "libft.h"

char	*get_next_line(int fd);
//size_t	ft_strlen(const char *s);
//size_t	ft_strlcpy(char *dst, const char *src, size_t size);
//char	*ft_strdup(const char *s);
char	*ft_strjoin_gnl(char *s1, const char *s2);
char	*ft_substr_gnl(char const *s, unsigned int start, size_t len);
char	*read_file(int fd, char *storage);
int		has_new_line(char *buffer);
char	*move_storage(char *storage);
char	*fill_line(const char *storage);

#endif