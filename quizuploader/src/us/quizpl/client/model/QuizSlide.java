package us.quizpl.client.model;

import com.google.gson.Gson;

public class QuizSlide {
	private int slideIndex;
	private String imagePath;
	private String text;
	private QuizPresentation parent;
	
	public static QuizSlide create(QuizPresentation parent, int index, String text, String imagePath) {
		QuizSlide slide = new QuizSlide();
		slide.parent = parent;
		slide.slideIndex = index;
		slide.text = text;
		slide.imagePath = imagePath;
		return slide;
	}
	
	public String getCanonicalName() {
		return String.format("%s/Slide%d.png", this.parent.getName(), this.slideIndex);
	}
	public String getLocalImagePath() {
		return this.imagePath;
	}
	public int getSlideIndex() {
		return this.slideIndex;
	}
	public String toJson(String docId) {
		AsJson serial = new AsJson(docId, this);
		return new Gson().toJson(serial);
	}
	
	private static class AsJson {
		private String presentationid;
		private String imageurl;
		private String textcontent;
		private String slideindex;
		
		private AsJson(String prId, QuizSlide slide) {
			this.presentationid = prId;
			this.imageurl = slide.getCanonicalName();
			this.slideindex = Integer.toString(slide.slideIndex);
			this.textcontent = slide.text;
		}
	}
}
