/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_delimiters.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 04:39:27 by auplisas          #+#    #+#             */
/*   Updated: 2025/01/13 06:36:56 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_exit_code_delim(char *str, int idx)
{
	if (idx - 1 < 0)
		return (false);
	if ((str[idx] == '?' && str[idx - 1] == '$') || (str[idx] == '/' && str[idx
			- 1] == '$'))
		return (true);
	return (false);
}

int countrows_delimiters(char const *src, bool delim(char c))
{
    int count = 0;
    int i = 0;

    while (src[i] != '\0')
    {
        if (delim(src[i]))
        {
            count++;
            i++;
        }
        else
        {
            while (src[i] != '\0' && !delim(src[i]))
                i++;
            count++;
        }
    }
    return count;
}

char **free_all_delimiters(char **parentarray, int arrayindex)
{
    int j = 0;
    while (j < arrayindex)
    {
        free(parentarray[j]);
        j++;
    }
    free(parentarray);
    return NULL;
}

char *allocate_and_copy_delimiters(const char *s, int startindex, int count)
{
    char *subarray = (char *)malloc(sizeof(char) * (count + 1));
    if (subarray == NULL)
        return NULL;
    ft_memcpy(subarray, &s[startindex], count);
    subarray[count] = '\0';
    return subarray;
}

char **str_div_logic_delimiters(char **parentarray, const char *s, bool delim(char c), int ar_index)
{
    int i = 0;
    int count;
    int startindex;

    while (s[i] != '\0')
    {
        if (delim(s[i]))
        {
            parentarray[ar_index] = allocate_and_copy_delimiters(s, i, 1);
            if (parentarray[ar_index++] == NULL)
                return free_all_delimiters(parentarray, ar_index);
            i++;
        }
        else
        {
            startindex = i;
            while (s[i] != '\0' && !delim(s[i]))
                i++;
            count = i - startindex;
            parentarray[ar_index] = allocate_and_copy_delimiters(s, startindex, count);
            if (parentarray[ar_index++] == NULL)
                return free_all_delimiters(parentarray, ar_index);
        }
    }
    return parentarray;
}

char **ft_split_delimiters(const char *s, bool delim(char c))
{
    char **parentarray;
    int ar_index;

    if (s == NULL)
    {
        return NULL;
    }

    ar_index = 0;
    parentarray = (char **)malloc(sizeof(char *) * (countrows_delimiters(s, delim) + 1));
    if (parentarray == NULL)
    {
        return NULL;
    }

    if (str_div_logic_delimiters(parentarray, s, delim, ar_index) == NULL)
    {
        return NULL;
    }

    parentarray[countrows_delimiters(s, delim)] = NULL;
    return parentarray;
}