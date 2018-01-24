package us.quizpl.search;

import java.util.ArrayList;
import java.util.Date;

public class QuizResult {
	
	public Date getDate() {
		return m_date;
	}
	public void setDate(Date date) {
		m_date = date;
	}
	public String getName() {
		return m_name;
	}
	public void setName(String name) {
		m_name = name;
	}
	public String getAuthor() {
		return m_author;
	}
	public void setAuthor(String author) {
		m_author = author;
	}
	
	public ArrayList<String> getSlideImageUrls() {
		return m_slideImageUrls;
	}

	public ArrayList<String> getSlideImageThumbs() {
		return m_slideImageThumbs;
	}
	
	@Override
	public boolean equals(Object obj) {
		// coz, nothing compares to you
		return false;
	}

	private String m_name;
	private Date m_date;
	private String m_author;
	private ArrayList<String> m_slideImageUrls = new ArrayList<String>();
	private ArrayList<String> m_slideImageThumbs = new ArrayList<String>();
}
