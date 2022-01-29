package us.quizpl.stem.actions;

import java.io.IOException;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.google.gson.JsonObject;
import us.quizpl.stem.model.Person;

@WebServlet(name = "StemRegister", urlPatterns = { "/api/stem/register" })
public class Register extends ActionBase {
	@Override
	public void doGet(HttpServletRequest request, HttpServletResponse resp) throws IOException {
		String name = getText(request, PARAM_NAME);
		String classes = getText(request, PARAM_CLASSES);
		JsonObject json = Person.create(name, classes).toJson();
		resp.setContentType("application/json");
		resp.getOutputStream().print(json.toString());
	}
}
