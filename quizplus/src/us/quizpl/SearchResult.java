package us.quizpl;

import org.apache.commons.lang3.StringEscapeUtils;
import com.google.appengine.api.search.ScoredDocument;
import us.quizpl.model.Presentation;
import us.quizpl.model.Slide;

public class SearchResult
{
	public SearchResult(String snippet, String author, String quiz) {
		setSnippet(snippet);
		setAuthor(author);
		setQuiz(quiz);
	}
	
	private SearchResult() {
		
	}
	
	public static SearchResult fromScoredDocument(ScoredDocument doc) {
		SearchResult result = new SearchResult();
		Slide slide = new Slide(doc);
		Presentation pres = slide.getPresentation();
		result.setQuiz(pres.getName());
		result.setAuthor(pres.getAuthor().getName());
		result.setSnippet(StringEscapeUtils.escapeEcmaScript(slide.getTextContent()));
		result.setRank(doc.getRank());
		
		
		return result;
	}
	
	public String getSnippet() {
		return m_snippet;
	}

	private void setSnippet(String snippet) {
		m_snippet = snippet;
	}

	public String getAuthor() {
		return m_author;
	}

	private void setAuthor(String author) {
		m_author = author;
	}

	public String getQuiz() {
		return m_quiz;
	}

	private void setQuiz(String quiz) {
		m_quiz = quiz;
	}

	public int getRank() {
		return m_rank;
	}

	private void setRank(int rank) {
		m_rank = rank;
	}

	private String m_snippet;
	private String m_author;
	private String m_quiz;
	private int m_rank;
}
