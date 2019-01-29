package us.quizpl.client.model;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.List;

import com.google.gson.Gson;

public class QuizPresentation {
	private String name;
	private String author;
	private LocalDate date;
	private List<QuizSlide> slides = new ArrayList<>();
	
	public String getName() {
		return name;
	}
	public String getAuthor() {
		return author;
	}
	public LocalDate getDate() {
		return date;
	}
	
	public static QuizPresentation create(String name, String author, String dateAsString) {
		QuizPresentation quiz = new QuizPresentation();
		quiz.name = name;
		quiz.author = author;
		if (dateAsString == null || dateAsString.isEmpty()) {
			quiz.date = LocalDate.now();
		} else {
			quiz.date = LocalDate.parse(dateAsString, DateTimeFormatter.ISO_LOCAL_DATE);
		}
		return quiz;
	}
	public QuizPresentation addSlide(QuizSlide slide) {
		this.slides.add(slide);
		return this;
	}
	public List<QuizSlide> getSlides() {
		return this.slides;
	}
	public String toJson() {
		AsJson serial = new AsJson();
		serial.name = this.name;
		serial.author = this.author;
		serial.date = this.date.format(DateTimeFormatter.ISO_LOCAL_DATE);
		serial.slidecount = this.slides.size();
		return new Gson().toJson(serial);
	}
	
	private static class AsJson {
		private String name;
		private String author;
		private String date;
		private int slidecount;
	}
}
