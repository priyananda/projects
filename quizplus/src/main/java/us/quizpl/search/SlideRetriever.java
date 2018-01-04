package us.quizpl.search;

import java.util.ArrayList;

import javax.servlet.http.HttpServletRequest;

import com.google.appengine.api.search.Results;
import com.google.appengine.api.search.ScoredDocument;

import us.quizpl.model.Presentation;
import us.quizpl.model.Slide;

public class SlideRetriever {

	public static ArrayList<String> getSlideAndNeighbours(HttpServletRequest request) {
		String slideId = request.getParameter(FIELD_SLIDEID);
		boolean isDevAppServer = request.getServerName().equalsIgnoreCase("localhost");
		
		Slide currentSlide = Slide.getById(slideId);
		Presentation presentation = currentSlide.getPresentation();
		
		int currentSlideIndex = currentSlide.getSlideIndex();
		int prevSlideIndex = -1;
		int nextSlideIndex = -1;
		
		boolean fNeedsQuery = false;
		if (currentSlideIndex > 0) {
			prevSlideIndex = currentSlideIndex - 1;
			fNeedsQuery = true;
		}
		if (currentSlideIndex < presentation.getSlideCount()) {
			nextSlideIndex = currentSlideIndex + 1;
			fNeedsQuery = true;
		}
		ArrayList<String> imageUrls = new ArrayList<String>();
		imageUrls.add(getImageFromSlide(currentSlide, isDevAppServer));
		
		if (fNeedsQuery) {
			Results<ScoredDocument> resultDocs = SearchEngine.getIndex().search(
				String.format("%s: %d AND %s:(%d OR %d)",
					Slide.FIELD_PRESENTATIONID, presentation.getId(),
					Slide.FIELD_SLIDEINDEX, prevSlideIndex, nextSlideIndex
				));
			for (ScoredDocument scoredDoc : resultDocs) {
				Slide slide = new Slide(scoredDoc);
				if (slide.getSlideIndex() == prevSlideIndex)
					imageUrls.add(0, getImageFromSlide(slide, isDevAppServer));
				else if (slide.getSlideIndex() == nextSlideIndex)
					imageUrls.add(getImageFromSlide(slide, isDevAppServer));
			}
		}
		
		return imageUrls;
	}
	
	private static String getImageFromSlide(Slide slide, boolean isDevAppServer) {
		if (isDevAppServer)
			return Math.random() > 0.5 ? "/test/Slide1.jpg" : "/test/Slide2.jpg";
		else
			return slide.getImageUrl();
	}

	private static final String FIELD_SLIDEID = "slideid";
}
