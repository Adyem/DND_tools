#include "CMA.hpp"

static int	ft_count_words(const char *s, char c)
{
	int	words;
	int	i;

	words = 0;
	i = 0;
	while (s[i])
	{
		if (i == 0 && s[i] != c)
			words++;
		if (i > 0 && s[i] != c && s[i - 1] == c)
			words++;
		i++;
	}
	return (words);
}

static char	**ft_malloc_strs(char **strs, const char *s, char c, bool critical)
{
	int	count;
	int	i;
	int	x;

	count = 0;
	i = 0;
	x = 0;
	while (s[i])
	{
		if (s[i] != c)
			count++;
		if ((s[i] == c && i > 0 && s[i - 1] != c)
			|| (s[i] != c && s[i + 1] == '\0'))
		{
			strs[x] = (char *)cma_malloc(sizeof(char) * (count + 1), critical);
			if (!strs[x])
				return (nullptr);
			count = 0;
			x++;
		}
		i++;
	}
	return (strs);
}

static char	**ft_cpy_strs(char **strs, const char *s, char c)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = 0;
	y = 0;
	while (s[i])
	{
		if (s[i] != c)
			strs[x][y++] = s[i];
		if (s[i] != c && s[i + 1] == '\0')
			strs[x][y] = '\0';
		if (s[i] == c && i > 0 && s[i - 1] != c)
		{
			strs[x][y] = '\0';
			x++;
			y = 0;
		}
		i++;
	}
	return (strs);
}

static char	**ft_merror(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		cma_free(strs[i]);
		strs[i] = nullptr;
		i++;
	}
	cma_free(strs);
	return (nullptr);
}

char	**ft_split(char const *s, char c, bool critical)
{
	char	**strs;
	int		wordcount;

	if (!s)
	{
		strs = (char **)cma_malloc(sizeof(char) * 1, critical);
		if (!strs)
			return (nullptr);
		*strs = nullptr;
		return (strs);
	}
	wordcount = ft_count_words(s, c);
	strs = (char **)cma_malloc(sizeof(*strs) * (wordcount + 1), critical);
	if (!strs)
		return (nullptr);
	if (ft_malloc_strs(strs, s, c, critical))
	{
		ft_cpy_strs(strs, s, c);
		strs[wordcount] = nullptr;
	}
	else
		strs = ft_merror(strs);
	return (strs);
}