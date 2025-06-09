/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isainz-r <isainz-r@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 10:52:45 by isainz-r          #+#    #+#             */
/*   Updated: 2024/10/18 12:32:20 by isainz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdint.h>

/**
 * @brief Allocates memory for an array and initializes all bytes to zero.
 * 
 * This function allocates memory for an array of `count` elements of `size`
 * bytes each and sets all allocated bytes to zero. If `count` or `size` is
 * too large, it returns NULL to avoid overflow.
 * 
 * @param count Number of elements to allocate.
 * @param size Size of each element in bytes.
 * 
 * @return Pointer to the allocated memory initialized to zero, or NULL on 
 *         failure.
 */
void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*pointer;
	size_t			i;

	if (count == SIZE_MAX || size == SIZE_MAX)
		return (0);
	pointer = malloc(count * size);
	if (!pointer)
		return (NULL);
	i = 0;
	while (i < count * size)
	{
		pointer[i] = '\0';
		i++;
	}
	return ((void *)pointer);
}

/**
 * @brief Calculates the length of a null-terminated string.
 * 
 * This function returns the number of characters in the string `s` before
 * the terminating null byte. If `s` is NULL, it returns 0.
 * 
 * @param s Pointer to the null-terminated string.
 * 
 * @return Length of the string, or 0 if `s` is NULL.
 */
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

/**
 * @brief Concatenates two strings into a new allocated string.
 * 
 * This function allocates and returns a new string which is the result of
 * the concatenation of `s1` followed by `s2`. If allocation fails, returns
 * NULL. If either string is NULL or empty, it handles appropriately.
 * 
 * @param s1 First input string.
 * @param s2 Second input string.
 * 
 * @return Newly allocated string containing the concatenation, or NULL on
 *         failure.
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*resultado;
	size_t	i;
	size_t	j;
	size_t	len_s1;
	size_t	len_s2;

	i = 0;
	j = 0;
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	resultado = ft_calloc(len_s1 + len_s2 + 1, 1);
	if (!resultado)
		return (NULL);
	while (i < len_s1 && s1[0] != '\0')
		resultado[j++] = s1[i++];
	i = 0;
	while (i < len_s2 && s2[0] != '\0')
		resultado[j++] = s2[i++];
	return (resultado);
}

/**
 * @brief Locates the first occurrence of a character in a string.
 * 
 * This function searches for the first occurrence of character `c` in the
 * string `s`. If `c` is `'\0'`, it returns a pointer to the string terminator.
 * Returns NULL if `s` is NULL or if character is not found.
 * 
 * @param s The null-terminated string to be searched.
 * @param c The character to find (converted to char).
 * 
 * @return Pointer to the first occurrence of `c` in `s`, or NULL if not found.
 */
char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if ((char)c == '\0')
		return ((char *) &s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *) &s[i]);
		i++;
	}
	return (0);
}

/**
 * @brief Creates a substring from a given string.
 * 
 * This function allocates and returns a substring from string `s`, starting
 * at index `start` and of maximum length `len`. If `start` is beyond the end
 * of `s` or `len` is zero, it returns an empty string. Returns NULL on failure.
 * 
 * @param s The original null-terminated string.
 * @param start Starting index of the substring.
 * @param len Maximum length of the substring.
 * 
 * @return Newly allocated substring, or NULL if allocation fails.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub_string;

	if (start > ft_strlen(s) || s[0] == '\0' || len == 0)
	{
		sub_string = malloc(1 * sizeof(char));
		if (!sub_string)
			return (NULL);
		sub_string[0] = '\0';
		return ((char *)sub_string);
	}
	if (len > (ft_strlen(s) - start))
		len = ft_strlen(s) - start;
	sub_string = malloc(len + 1 * sizeof(char));
	if (!sub_string)
		return (NULL);
	i = 0;
	while (i < len)
		sub_string[i++] = s[start++];
	sub_string[i] = '\0';
	return ((char *)sub_string);
}
