struct ft_nullptr_t
{
	    template <typename T>
	    operator T*() const { return 0; }

	    template <typename C, typename T>
	    operator T C::*() const { return 0; }

	private:
	    void operator&() const;
};

const ft_nullptr_t ft_nullptr = {};
