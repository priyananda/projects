package us.quizpl.app;

import java.io.IOException;
import javax.servlet.http.*;
import com.google.gson.JsonObject;
import us.quizpl.app.model.PrelimsState;

@SuppressWarnings("serial")
public class PrelimsGetter extends HttpServlet {

	public void doGet(HttpServletRequest req, HttpServletResponse resp) throws IOException {
		resp.setContentType("application/json");
		JsonObject jsonObject = PrelimsState.getPrelimsStateAsJson();
		resp.getOutputStream().print(jsonObject.toString());
	}
	public void doPost(HttpServletRequest req, HttpServletResponse resp) throws IOException {
		doGet(req, resp);
	}
}