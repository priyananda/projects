package us.quizpl.search;

import javax.servlet.http.HttpServletRequest;

import com.google.appengine.api.search.Query;
import com.google.appengine.api.search.QueryOptions;
import com.google.appengine.api.search.Results;
import com.google.appengine.api.search.ScoredDocument;
import com.google.appengine.api.search.SortExpression;
import com.google.appengine.api.search.SortOptions;

import us.quizpl.model.Presentation;
import us.quizpl.model.Slide;

public class QuizRetriever {
	public static QuizResult find(HttpServletRequest request) {
		String presentationId = request.getParameter(FIELD_ID);
		
		if (presentationId == null)
			return null;
		
		Presentation presentation = Presentation.getById(Long.parseLong(presentationId));
		if (presentation == null)
			return null;
		
		QuizResult result = new QuizResult();
		final boolean isDevAppServer = request.getServerName().equalsIgnoreCase("localhost");
		result.setName(presentation.getName());
		result.setDate(presentation.getDate());
		result.setAuthor(presentation.getAuthor().getName());
		
		SortOptions sortOptions = SortOptions.newBuilder()
	      .addSortExpression(SortExpression.newBuilder()
	          .setExpression(Slide.FIELD_SLIDEINDEX)
	          .setDirection(SortExpression.SortDirection.ASCENDING))
	      .build();
		
		QueryOptions queryOptions = QueryOptions.newBuilder()
	      .setSortOptions(sortOptions)
	      .build();
		
		Query query = Query.newBuilder()
			.setOptions(queryOptions)
			.build(String.format("%s: %d", Slide.FIELD_PRESENTATIONID, presentation.getId()));
		
		Results<ScoredDocument> resultDocs = SearchEngine.getIndex().search(query);
		
		for (ScoredDocument scoredDoc : resultDocs) {
			Slide slide = new Slide(scoredDoc);
			result.getSlideImageUrls().add(getImageFromSlide(slide, isDevAppServer));
			result.getSlideImageThumbs().add(getThumbnailFromSlide(slide, isDevAppServer));
		}
		
		return result;
	}
	
	private static String getImageFromSlide(Slide slide, boolean isDevAppServer) {
		if (isDevAppServer)
			return Math.random() > 0.5 ? "/test/Slide1.jpg" : "/test/Slide2.jpg";
		else
			return slide.getImageUrl();
	}
	
	private static String getThumbnailFromSlide(Slide slide, boolean isDevAppServer) {
		if (isDevAppServer)
			return Math.random() > 0.5 ? "/test/Slide1.jpg" : "/test/Slide2.jpg";
		else
			return slide.getThumbnailUrl();
	}
	
	private static final String FIELD_ID = "id";
}
