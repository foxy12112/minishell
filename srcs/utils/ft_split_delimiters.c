/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_delimiters.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 04:39:27 by auplisas          #+#    #+#             */
/*   Updated: 2025/01/15 10:16:15 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_delimiter(char c)
{
	if (c == '"' || c == '\'')
		return (true);
	if (c == ' ')
		return (true);
	return (false);
}

// int	countrows_delimiters(char const *src)
// {
// 	int	count;
// 	int	i;

// 	count = 0;
// 	i = 0;
// 	while (src[i] != '\0')
// 	{
// 		if (is_delimiter(src[i]))
// 		{
// 			count++;
// 			i++;
// 		}
// 		else if (src[i] == '$')
// 		{
//             i++;
//             count++;
// 		}
// 		else
// 		{
// 			while (src[i] != '\0' && !is_delimiter(src[i]) && src[i] != '$')
// 				i++;
// 			count++;
// 		}
// 	}
// 	return (count);
// }

int	countrows_delimiters(char const *src)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (src[i] != '\0')
	{
		if (src[i] == ' ' || src[i] == '\'' || src[i] == '"')
		{
			count++;
			i++;
		}
		else if (src[i] == '$')
		{
			count++;
			i++;
			while (src[i] != '\0' && src[i] != ' ' && src[i] != '\''
				&& src[i] != '"' && src[i] != '$')
			{
				i++;
			}
		}
		else
		{
			count++;
			while (src[i] != '\0' && src[i] != ' ' && src[i] != '\''
				&& src[i] != '"' && src[i] != '$')
			{
				i++;
			}
		}
	}
	// printf("Count is: %d\n", count);
	return (count);
}

char	**free_all_delimiters(char **parentarray, int arrayindex)
{
	int	j;

	j = 0;
	while (j < arrayindex)
	{
		free(parentarray[j]);
		j++;
	}
	free(parentarray);
	return (NULL);
}

char	*allocate_and_copy_delimiters(const char *s, int startindex, int count)
{
	char	*subarray;

	subarray = (char *)malloc(sizeof(char) * (count + 1));
	if (subarray == NULL)
		return (NULL);
	ft_memcpy(subarray, &s[startindex], count);
	subarray[count] = '\0';
	return (subarray);
}

char	**str_div_logic_delimiters(char **parentarray, const char *s,
		int ar_index)
{
	int	i;
	int	count;
	int	startindex;

	i = 0;
	while (s[i] != '\0')
	{
		if (is_delimiter(s[i]))
		{
			parentarray[ar_index] = allocate_and_copy_delimiters(s, i, 1);
			if (parentarray[ar_index++] == NULL)
				return (free_all_delimiters(parentarray, ar_index));
			i++;
		}
		else if (s[i] == '$')
		{
			startindex = i;
			i++;
			while (s[i] != '\0' && s[i] != '$' && !is_delimiter(s[i]))
				i++;
			count = i - startindex;
			parentarray[ar_index] = allocate_and_copy_delimiters(s, startindex,
					count);
			if (parentarray[ar_index++] == NULL)
				return (free_all_delimiters(parentarray, ar_index));
		}
		else
		{
			startindex = i;
			while (s[i] != '\0' && s[i] != '$' && !is_delimiter(s[i]))
				i++;
			count = i - startindex;
			parentarray[ar_index] = allocate_and_copy_delimiters(s, startindex,
					count);
			if (parentarray[ar_index++] == NULL)
				return (free_all_delimiters(parentarray, ar_index));
		}
	}
	return (parentarray);
}

char	**ft_split_delimiters(const char *s)
{
	char	**parentarray;
	int		ar_index;

	if (s == NULL)
	{
		return (NULL);
	}
	ar_index = 0;
	parentarray = (char **)malloc(sizeof(char *) * (countrows_delimiters(s)
				+ 1));
	if (parentarray == NULL)
	{
		return (NULL);
	}
	if (str_div_logic_delimiters(parentarray, s, ar_index) == NULL)
	{
		return (NULL);
	}
	parentarray[countrows_delimiters(s)] = NULL;
	return (parentarray);
}

// int countrows_delimiters(char const *src)
// {
//     int count = 0;
//     int i = 0;

//     while (src[i] != '\0')
//     {
//         if (is_delimiter(src[i]))
//         {
//             count++;
//             i++;
//         }
//         else
//         {
//             while (src[i] != '\0' && !is_delimiter(src[i]))
//                 i++;
//             count++;
//         }
//     }
//     return (count);
// }

// char **free_all_delimiters(char **parentarray, int arrayindex)
// {
//     int j = 0;
//     while (j < arrayindex)
//     {
//         free(parentarray[j]);
//         j++;
//     }
//     free(parentarray);
//     return (NULL);
// }

// char *allocate_and_copy_delimiters(const char *s, int startindex, int count)
// {
//     char *subarray = (char *)malloc(sizeof(char) * (count + 1));
//     if (subarray == NULL)
//         return (NULL);
//     ft_memcpy(subarray, &s[startindex], count);
//     subarray[count] = '\0';
//     return (subarray);
// }

// char **str_div_logic_delimiters(char **parentarray, const char *s,int ar_index)
// {
//     int i = 0;
//     int count;
//     int startindex;

//     while (s[i] != '\0')
//     {
//         if (is_delimiter(s[i]))
//         {
//             parentarray[ar_index] = allocate_and_copy_delimiters(s, i, 1);
//             if (parentarray[ar_index++] == NULL)
//                 return (free_all_delimiters(parentarray, ar_index));
//             i++;
//         }
//         else
//         {
//             startindex = i;
//             while (s[i] != '\0' && !is_delimiter(s[i]))
//                 i++;
//             count = i - startindex;
//             parentarray[ar_index] = allocate_and_copy_delimiters(s,startindex, count);
//             if (parentarray[ar_index++] == NULL)
//                 return (free_all_delimiters(parentarray, ar_index));
//         }
//     }
//     return (parentarray);
// }

// char **ft_split_delimiters(const char *s)
// {
//     char **parentarray;
//     int ar_index;

//     if (s == NULL)
//     {
//         return (NULL);
//     }

//     ar_index = 0;
//     parentarray = (char **)malloc(sizeof(char *) * (countrows_delimiters(s)+ 1));
//     if (parentarray == NULL)
//     {
//         return (NULL);
//     }

//     if (str_div_logic_delimiters(parentarray, s, ar_index) == NULL)
//     {
//         return (NULL);
//     }

//     parentarray[countrows_delimiters(s)] = NULL;
//     return (parentarray);
// }