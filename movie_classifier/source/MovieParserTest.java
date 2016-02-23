public class MovieParserTest
{
	public static void main(String[] args)
	{
		try 
		{
			MovieParser parser = new MovieParser("../input/ml-latest-small/movies.csv");
			parser.forEach( (movie) -> { System.out.println("ID: " + movie.getId() + ", title: " + movie.getTitle());});
		}catch(Exception e) {
			e.printStackTrace();
		}
	}
}
