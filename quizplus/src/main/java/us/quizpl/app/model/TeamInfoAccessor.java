package us.quizpl.app.model;
import com.google.gson.JsonObject;

public interface TeamInfoAccessor {
	public JsonObject getTeamsAsJson();
	public void updateStateFromJson(JsonObject jsonObj);
}