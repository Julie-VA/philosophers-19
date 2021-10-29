/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-aud <rvan-aud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 12:08:32 by rvan-aud          #+#    #+#             */
/*   Updated: 2021/10/29 13:43:35 by rvan-aud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*dest;
	int		i;
	int		l;

	i = 0;
	l = ft_strlen(s);
	dest = (char *)malloc(sizeof(char) * (l + 1));
	if (!dest)
		return (NULL);
	while (i < l)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	get_lens(const char *s1, const char *s2, int *lens1, int *lens2)
{
	*lens1 = ft_strlen(s1);
	*lens2 = ft_strlen(s2);
}

char	*mod_strjoin(char const *s1, char const *s2, int mod)
{
	char	*str;
	int		lens1;
	int		lens2;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (ft_strdup(""));
	get_lens(s1, s2, &lens1, &lens2);
	str = (char *)malloc(sizeof(char) * (lens1 + lens2 + 2));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	if (!mod)
		str[j++] = ' ';
	else
		str[j++] = '\n';
	str[j] = '\0';
	return (str);
}
