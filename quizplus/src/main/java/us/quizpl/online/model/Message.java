package us.quizpl.online.model;

import java.time.LocalDateTime;
import java.time.ZoneId;
import java.time.format.DateTimeFormatter;

import com.google.appengine.api.datastore.Entity;
import com.google.gson.JsonObject;

import us.quizpl.model.ModelObjectBase;

public class Message extends ModelObjectBase {
	public Message(Entity entity) {
		super(entity);
	}
	
	public static Message getById(long id) {
		Message message = new Message(null);
		ModelObjectBase.loadObject(message, ENTITY_NAME, id);
		return message;
	}
	
	public static Message create(long channel, String name, String messageText) {
		Entity entity = new Entity(ENTITY_NAME);
		
		entity.setProperty(FIELD_CHANNEL, channel);
		entity.setProperty(FIELD_NAME, name);
		entity.setProperty(FIELD_MESSAGE, messageText);
		entity.setProperty(FIELD_DATE, LocalDateTime.now(ZoneId.of("America/Los_Angeles")).toString());
		
		Message message = new Message(entity);
		message.save();
		return message;
	}
	

	public String getName() {
		return (String) m_entity.getProperty(FIELD_NAME);
	}
	
	public long getChannel() {
		return (long) m_entity.getProperty(FIELD_CHANNEL);
	}
	
	public String getText() {
		return (String) m_entity.getProperty(FIELD_MESSAGE);
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
		jsonObject.addProperty(FIELD_CHANNEL.toLowerCase(), getChannel());
		jsonObject.addProperty(FIELD_DATE.toLowerCase(),
			getDate().format(DateTimeFormatter.ofPattern("kk:mm yyyy-MM-dd")));
		jsonObject.addProperty(FIELD_MESSAGE.toLowerCase(), getText());
		return jsonObject;
	}
	
	public static final String ENTITY_NAME = "Message";
	public static final String FIELD_CHANNEL = "Channel";
	public static final String FIELD_NAME = "Name";
	public static final String FIELD_DATE = "Date";
	public static final String FIELD_MESSAGE = "Text";
}
