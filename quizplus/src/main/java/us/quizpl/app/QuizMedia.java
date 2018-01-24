package us.quizpl.app;

import java.io.IOException;
import java.util.ArrayList;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.google.apphosting.api.search.DocumentPb.Document.Storage;
import com.google.gson.JsonArray;
import com.google.gson.JsonObject;

import us.quizpl.StorageHelper;
import us.quizpl.model.Presentation;
import us.quizpl.model.Slide;
import us.quizpl.search.QuizResult;
import us.quizpl.search.QuizRetriever;

@WebServlet(
	name = "QuizMedia",
	urlPatterns = {"/qmedia"}
)
@SuppressWarnings("serial")
public class QuizMedia extends HttpServlet {
	public void doPost(HttpServletRequest req, HttpServletResponse resp) throws IOException, ServletException {
		doGet(req, resp);
	}
	public void doGet(HttpServletRequest req, HttpServletResponse resp) throws IOException {
		resp.setContentType("application/json");
		JsonObject jsonObject = getMediaJson(req);
		resp.getOutputStream().print(jsonObject.toString());
	}
	
	private JsonObject getMediaJson(HttpServletRequest request){
		String presentationId = request.getParameter("id");
	
		if (presentationId == null)
			return null;
		
		Presentation presentation = Presentation.getById(Long.parseLong(presentationId));
		long slideCount = presentation.getSlideCount();
		JsonArray jsonArray = new JsonArray();
		for (long i = 1; i <= slideCount; ++i) {
			String servingUrl = StorageHelper.getUrlForGcsFile(Slide.BUCKET_NAME,
				String.format("%1$s/Slide%2$d.jpg", presentation.getName(), i));
			jsonArray.add(toJsonObject(servingUrl));
		}
		JsonObject jobjOuter = new JsonObject();
		jobjOuter.add("imageInfo2", jsonArray);
		return jobjOuter;
	}
	
	private JsonObject toJsonObject(String url){
		JsonObject jsonObject = new JsonObject();
		jsonObject.addProperty("url", url);
		return jsonObject;
	}
}
