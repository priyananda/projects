package us.quizpl.client.upload;

import static java.nio.charset.StandardCharsets.UTF_8;

import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.net.URLEncoder;

import com.google.api.client.http.ByteArrayContent;
import com.google.api.client.http.GenericUrl;
import com.google.api.client.http.HttpRequest;
import com.google.api.client.http.HttpRequestFactory;
import com.google.api.client.http.HttpResponse;
import com.google.api.client.http.HttpTransport;
import com.google.api.client.http.javanet.NetHttpTransport;

import us.quizpl.client.model.QuizPresentation;
import us.quizpl.client.model.QuizSlide;

public class QuizModelUploader {
	static final HttpTransport HTTP_TRANSPORT = new NetHttpTransport();
	
	private String server;
	public QuizModelUploader(String server) {
		this.server = server + "/import";
	}
	public void uploadQuiz(QuizPresentation quiz) {
		try {
			String presentationId = uploadPresentation(quiz);
			for (QuizSlide slide : quiz.getSlides()) {
				uploadSlide(presentationId, slide);
			}
		} catch(Exception e) {
			throw new RuntimeException(e);
		}
	}
	private void uploadSlide(String presentationId, QuizSlide slide)  throws UnsupportedEncodingException, IOException {
		StringBuilder builder = new StringBuilder();
		appendParameter(builder, "slide", slide.toJson(presentationId));
		executeImport(builder.toString());
	}
	private String uploadPresentation(QuizPresentation quiz) throws UnsupportedEncodingException, IOException {
		StringBuilder builder = new StringBuilder();
		appendParameter(builder, "presentation", quiz.toJson());
		String docId = executeImport(builder.toString());
		return docId;
	}
	private void appendParameter(StringBuilder builder, String paramName, String jsonData)
			throws UnsupportedEncodingException {
		builder.append(paramName);
		builder.append("=");
		builder.append(URLEncoder.encode(jsonData, UTF_8.name()));
	}
	private String executeImport(String queryString) throws IOException {
		HttpRequestFactory requestFactory = HTTP_TRANSPORT.createRequestFactory();
		GenericUrl url = new GenericUrl(this.server);
		HttpRequest request = requestFactory.buildPostRequest(
			url, ByteArrayContent.fromString(null, queryString));
		request.getHeaders().setContentType("application/x-www-form-urlencoded");
		HttpResponse response = request.execute();
		String id = response.parseAsString();
		response.disconnect();
		return id;
	}
}
