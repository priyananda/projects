package us.quizpl.puzzle.model;

import java.time.LocalDateTime;
import java.time.ZoneId;
import java.util.Optional;

import com.google.appengine.api.datastore.DatastoreService;
import com.google.appengine.api.datastore.DatastoreServiceFactory;
import com.google.appengine.api.datastore.Entity;
import com.google.appengine.api.datastore.FetchOptions;
import com.google.appengine.api.datastore.Query;
import com.google.gson.JsonObject;

import us.quizpl.model.ModelObjectBase;

public class AnswerSubmission extends ModelObjectBase {
	public AnswerSubmission(Entity entity) {
		super(entity);
	}

	public static AnswerSubmission create(long personId, String key) {
		Entity entity = new Entity(ENTITY_NAME);

		entity.setProperty(FIELD_PID, personId);
		entity.setProperty(FIELD_KEY, key);
		entity.setProperty(FIELD_DATE, LocalDateTime.now(ZoneId.of("America/Los_Angeles")).toString());

		AnswerSubmission answer = new AnswerSubmission(entity);
		answer.save();
		return answer;
	}

	public long getPersonId() {
		return (long) m_entity.getProperty(FIELD_PID);
	}

	public String getKey() {
		return (String) m_entity.getProperty(FIELD_KEY);
	}

	public LocalDateTime getDate() {
		return LocalDateTime.parse((String) m_entity.getProperty(FIELD_DATE));
	}

	public long getId() {
		return m_entity.getKey().getId();
	}

	public static final String ENTITY_NAME = "Puzzle.AnswerSubmission";
	public static final String FIELD_PID = "Pid";
	public static final String FIELD_KEY = "Key";
	public static final String FIELD_DATE = "Date";
}
