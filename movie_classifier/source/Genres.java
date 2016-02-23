public class Genres
{
	public Genres()
	{
		m_bitmask = 0;
	}
	
	public void addGenre(Genre g) {
		m_bitmask |= (1 << g.ordinal());
	}
	
	public void removeGenre(Genre g) {
		m_bitmask &= ~(1 << g.ordinal());
	}
	
	public boolean hasGenre(Genre g) {
		if (g == Genre.None)
			return (m_bitmask == 0);
		return ((m_bitmask & (1 << g.ordinal())) != 0);
	}

	private int m_bitmask;
}
