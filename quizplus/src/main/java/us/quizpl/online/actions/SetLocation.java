package us.quizpl.online.actions;

import java.io.IOException;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.google.gson.JsonObject;

import us.quizpl.online.model.Person;

@WebServlet(name = "OnlineSetLocation", urlPatterns = { "/api/olq/setlocation" })
public class SetLocation extends ActionBase {

	@Override
	public void doGet(HttpServletRequest request, HttpServletResponse resp) throws IOException {
		boolean succeeded = trySetLocation(request);
		resp.setContentType("application/json");
		JsonObject json = new JsonObject();
		json.addProperty("success", succeeded);
		resp.getOutputStream().print(json.toString());
	}

	boolean trySetLocation(HttpServletRequest request) {
		try {
			long pid = getLong(request, PARAM_PERSON);
			long qid = getLong(request, PARAM_QUESTION);
			Person.getById(pid).setLocation(qid).save();
			return true;
		} catch (Exception e) {
			return false;
		}
	}
}
