package us.quizpl.jan21.model;

import java.time.LocalDateTime;
import java.time.ZoneId;
import java.time.format.DateTimeFormatter;

import com.google.appengine.api.datastore.Entity;
import com.google.gson.JsonObject;

import us.quizpl.model.ModelObjectBase;

public class AnswerAttempt extends ModelObjectBase {
	public AnswerAttempt(Entity entity) {
		super(entity);
	}
	
	public static AnswerAttempt getById(long id) {
		AnswerAttempt message = new AnswerAttempt(null);
		ModelObjectBase.loadObject(message, ENTITY_NAME, id);
		return message;
	}
	
	public static AnswerAttempt create(long team, String set, long question, String name, String answerText) {
		Entity entity = new Entity(ENTITY_NAME);
		
		entity.setProperty(FIELD_TEAM, team);
		entity.setProperty(FIELD_NAME, name);
		entity.setProperty(FIELD_SET, set);
		entity.setProperty(FIELD_TEXT, answerText);
		entity.setProperty(FIELD_QUESTION, question);
		entity.setProperty(FIELD_DATE, LocalDateTime.now(ZoneId.of("America/Los_Angeles")).toString());
		
		AnswerAttempt message = new AnswerAttempt(entity);
		message.save();
		return message;
	}
	

	public String getName() {
		return (String) m_entity.getProperty(FIELD_NAME);
	}
	
	public long getTeam() {
		return (long) m_entity.getProperty(FIELD_TEAM);
	}
	
	public String getQuestionSet() {
		return (String)m_entity.getProperty(FIELD_SET);
	}
	
	public long getQuestion() {
		return (long) m_entity.getProperty(FIELD_QUESTION);
	}
	
	public String getText() {
		return (String) m_entity.getProperty(FIELD_TEXT);
	}
	
	public LocalDateTime getDate() {
		return LocalDateTime.parse((String) m_entity.getProperty(FIELD_DATE));
	}
	
	public long getId() {
		return m_entity.getKey().getId();
	}
	
	public JsonObject toJson() {
		JsonObject jsonObject = new JsonObject();
		jsonObject.addProperty(FIELD_NAME.toLowerCase(), getName());
		jsonObject.addProperty(FIELD_TEAM.toLowerCase(), getTeam());
		jsonObject.addProperty(FIELD_QUESTION.toLowerCase(), getQuestion());
		jsonObject.addProperty(FIELD_SET.toLowerCase(), getQuestionSet());
		jsonObject.addProperty(FIELD_DATE.toLowerCase(),
			getDate().format(DateTimeFormatter.ofPattern("kk:mm yyyy-MM-dd")));
		jsonObject.addProperty(FIELD_TEXT.toLowerCase(), getText());
		return jsonObject;
	}
	
	public static final String ENTITY_NAME = "Jan21.AnswerAttempt";
	public static final String FIELD_TEAM = "Team";
	public static final String FIELD_NAME = "Name";
	public static final String FIELD_DATE = "Date";
	public static final String FIELD_SET = "Set";
	public static final String FIELD_QUESTION = "Question";
	public static final String FIELD_TEXT = "Text";
}
