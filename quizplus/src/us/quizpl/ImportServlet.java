package us.quizpl;
import java.io.IOException;
import java.util.Map.Entry;
import javax.servlet.http.*;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;

@SuppressWarnings("serial")
public class ImportServlet extends HttpServlet {
	public void doGet(HttpServletRequest req, HttpServletResponse resp) throws IOException {
		resp.setContentType("text/plain");
		
		String jsonData = (String) req.getParameter("slide");
		JsonParser parser = new JsonParser();
		JsonElement jsonElement = parser.parse(jsonData);
		JsonObject jsonObj = jsonElement.getAsJsonObject();
		
		StringBuilder outputString = new StringBuilder();
		for (Entry<String, JsonElement> attrib : jsonObj.entrySet()) {
			String name = attrib.getKey();
			String value = attrib.getValue().toString();
			outputString.append(name);
			outputString.append(" : ");
			outputString.append(value);
			outputString.append("\n");
		}
		
		resp.getOutputStream().print(outputString.toString());
	}
	public void doPost(HttpServletRequest req, HttpServletResponse resp) throws IOException {
		doGet(req, resp);
	}
}