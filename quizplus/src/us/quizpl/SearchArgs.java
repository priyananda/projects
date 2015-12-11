package us.quizpl;

import java.util.Date;
import java.util.List;

import javax.servlet.http.HttpServletRequest;

public class SearchArgs {
	
	public static SearchArgs fromRequest(HttpServletRequest request) {
		SearchArgs searchArgs = new SearchArgs();
		searchArgs.m_searchText = request.getParameter(FIELD_SEARCHTEXT);
		if (searchArgs.m_searchText == null)
			searchArgs.m_searchText = "";
		searchArgs.m_authors = request.getParameterValues(FIELD_AUTHOR);
		searchArgs.m_limit = DEFAULT_LIMIT;
		searchArgs.m_offset = DEFAULT_OFFSET;
		return searchArgs;
	}
	
	public String getSearchText() {
		return m_searchText;
	}

	public String[] getAuthors() {
		return m_authors;
	}

	public Date getDate() {
		return m_date;
	}

	public int getOffset() {
		return m_offset;
	}

	public int getLimit() {
		return m_limit;
	}

	private String m_searchText;
	private String[] m_authors;
	private Date m_date;
	private int m_offset;
	private int m_limit;
	
	private static final int DEFAULT_OFFSET = 0;
	private static final int DEFAULT_LIMIT = 100;
	
	private static final String FIELD_SEARCHTEXT = "field_search_text";
	private static final String FIELD_AUTHOR = "field_author";
	private static final String FIELD_DATE = "field_date";
}
