package us.quizpl;

import java.io.IOException;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;

@WebServlet(
	name = "Quizplus",
	urlPatterns = {"/quizplus"}
)
@SuppressWarnings("serial")
public class QuizplusServlet extends HttpServlet {
	public void doGet(HttpServletRequest req, HttpServletResponse resp) throws IOException {
		resp.setContentType("text/plain");
		resp.getWriter().println("Hello, world");
	}
}
