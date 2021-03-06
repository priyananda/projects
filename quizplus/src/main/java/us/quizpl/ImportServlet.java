package us.quizpl;
import java.io.IOException;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;

import us.quizpl.model.Presentation;
import us.quizpl.model.Slide;

@WebServlet(
	name = "Import",
	urlPatterns = {"/import"}
)
@SuppressWarnings("serial")
public class ImportServlet extends HttpServlet {
	
	
	public void doGet(HttpServletRequest req, HttpServletResponse resp) throws IOException {
		resp.setContentType("text/plain");
		
		JsonParser parser = new JsonParser();
		
		String jsonData = (String) req.getParameter("presentation");
		if (jsonData != null) {
			JsonObject jsonObj  = parser.parse(jsonData).getAsJsonObject();
			Presentation presentation = Presentation.create(jsonObj);
			resp.getOutputStream().print(Long.toString(presentation.getId()));
		}

		String[] slideParams = req.getParameterValues("slide");
		String authorNameCached = null;
		if (slideParams != null) {
			for( String jsonSlideData : slideParams) {
				JsonObject jsonObj  = parser.parse(jsonSlideData).getAsJsonObject();
				Slide slide = Slide.create(jsonObj, authorNameCached);
				if (authorNameCached == null)
					authorNameCached = slide.getAuthorName();
				resp.getOutputStream().print(
					String.format("Uploaded slide %s", slide.getId()));
			}
		}
	}
	public void doPost(HttpServletRequest req, HttpServletResponse resp) throws IOException {
		doGet(req, resp);
	}
}