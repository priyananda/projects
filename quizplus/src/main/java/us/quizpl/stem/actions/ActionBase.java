package us.quizpl.stem.actions;

import java.io.IOException;
import java.net.URLDecoder;
import java.nio.charset.StandardCharsets;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class ActionBase extends HttpServlet {
	public static final String PARAM_KEY = "k";
	public static final String PARAM_ANSWER = "a";
	public static final String PARAM_NAME = "n";
	public static final String PARAM_PERSON = "p";
	public static final String PARAM_CLASSES = "c";
	
	@Override
	public void doPost(HttpServletRequest req, HttpServletResponse resp) throws IOException, ServletException {
		doGet(req, resp);
	}
	
	protected static long getLong(HttpServletRequest req, String paramName) {
		return Long.parseLong(req.getParameter(paramName));
	}
	
	protected static String getText(HttpServletRequest request, String paramName) {
		try {
	     if (request.getParameter(paramName) == null)
	    	 return null;
		 return URLDecoder.decode(request.getParameter(paramName), StandardCharsets.UTF_8.name());
		} catch(Exception e) {
			throw new RuntimeException(e);
		}
	}
}
