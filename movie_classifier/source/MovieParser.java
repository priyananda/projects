import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.function.Consumer;

public class MovieParser
{
	public MovieParser(String filename) throws Exception
	{
		isFirstLine = true;
	
		BufferedReader reader = new BufferedReader(new FileReader(filename));
		String line;
		while ((line = reader.readLine()) != null)
		{
			parseLine(line);
		}
		reader.close();
	}
	
	public void forEach(Consumer<MovieEntry> visitor)
	{
		m_movies.forEach(visitor);
	}
	
	private void parseLine(String line)
	{
		if (isFirstLine) {
			isFirstLine = false;
			return;
		}
		
		int idxFirstComma = line.indexOf(',');
		int idxSecondComma = line.lastIndexOf(',');
		
		String strId     = line.substring(0, idxFirstComma);
		String strTitle  = line.substring(idxFirstComma + 1, idxSecondComma - idxFirstComma);
		String strGenres = line.substring(idxSecondComma + 1);
		
		strTitle = strTitle.replace("\"", "");
		
		m_movies.add(new MovieEntry(Integer.parseInt(strId), strTitle, null));
	}
	
	private ArrayList<MovieEntry> m_movies = new ArrayList<MovieEntry>();
	private boolean isFirstLine;
}
