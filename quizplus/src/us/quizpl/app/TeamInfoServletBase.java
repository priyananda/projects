package us.quizpl.app;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import us.quizpl.app.model.FinalsAccessor;
import us.quizpl.app.model.PrelimsAccessor;
import us.quizpl.app.model.TeamInfoAccessor;

@SuppressWarnings("serial")
public class TeamInfoServletBase extends HttpServlet {
	public void doPost(HttpServletRequest req, HttpServletResponse resp) throws IOException, ServletException {
		doGet(req, resp);
	}
	protected TeamInfoAccessor getAccessor(HttpServletRequest req){
		String mode = req.getParameter("mode");
		if ("prelims".equals(mode))
			return new PrelimsAccessor();
		return new FinalsAccessor();
	}
}
