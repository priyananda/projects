package us.quizpl.client;

import com.google.devtools.common.options.Option;
import com.google.devtools.common.options.OptionsBase;

public class UploadOptions extends OptionsBase {
	@Option(
		name = "input_path",
		defaultValue = "")
	public String inputPath;
	
	@Option(
		name = "quiz_name",
		defaultValue = "")
	public String quizName;
	
	@Option(
		name = "author",
		defaultValue = "")
	public String authorName;
	
	@Option(
		name = "date",
		defaultValue = "")
	public String dateAsString;
	
	@Option(
		name = "server",
		defaultValue = "http://localhost:8080")
	public String server;
	
	@Option(
		name = "skip_image_upload",
		defaultValue = "false")
	public boolean skipImageUpload;
}
