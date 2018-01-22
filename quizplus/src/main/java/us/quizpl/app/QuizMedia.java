package us.quizpl.app;

import java.io.IOException;
import java.util.ArrayList;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.google.gson.JsonArray;
import com.google.gson.JsonObject;

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
		QuizResult result = QuizRetriever.find(request);
		ArrayList<String> imageUrls = result.getSlideImageUrls();
		
		JsonArray jsonArray = new JsonArray();
		for(String url : imageUrls) {
			jsonArray.add(toJsonObject(url));
		}
		
		JsonObject jobjOuter = new JsonObject();
		jobjOuter.add("imageInfo", jsonArray);
		return jobjOuter;
	}
	
	private JsonObject toJsonObject(String url){
		JsonObject jsonObject = new JsonObject();
		jsonObject.addProperty("url", url);
		return jsonObject;
	}
}
