public class MovieEntry
{
	public MovieEntry(int i, String t, Genres gs)
	{
		this.id = i;
		this.title = t;
		this.genres = gs;
	}

	public int getId() {
		return id;
	}
	
	public String getTitle() {
		return title;
	}
	
	public Genres getGenres() {
		return genres;
	}

	private int id;
	private String title;
	private Genres genres;
}
