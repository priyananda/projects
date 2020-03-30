package us.quizpl.online.actions;

import java.io.IOException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import us.quizpl.online.model.Message;
import us.quizpl.online.model.Team;

@WebServlet(name = "OnlinePostMessage", urlPatterns = { "/api/olq/postmessage" })
public class PostMessage extends ActionBase {
	public void doGet(HttpServletRequest request, HttpServletResponse resp) throws IOException {
		long channelId = getLong(request, PARAM_CHANNEL);
		String name = getText(request, PARAM_NAME);
		String messageText = getText(request, PARAM_MESSAGE);
		
		Message.create(channelId, name, messageText);
		resp.setContentType("application/json");
		resp.getOutputStream().print(Team.getTeamData(channelId).toString());
	}
}
