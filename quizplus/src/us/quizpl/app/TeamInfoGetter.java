package us.quizpl.app;

import java.io.IOException;
import javax.servlet.http.*;
import com.google.gson.JsonObject;

@SuppressWarnings("serial")
public class TeamInfoGetter extends TeamInfoServletBase {

	public void doGet(HttpServletRequest req, HttpServletResponse resp) throws IOException {
		resp.setContentType("application/json");
		JsonObject jsonObject = getAccessor(req).getTeamsAsJson();
		resp.getOutputStream().print(jsonObject.toString());
	}
	
}