package us.quizpl.model;

import java.time.LocalDate;
import java.time.format.DateTimeFormatter;

import com.google.appengine.api.datastore.Entity;
import com.google.gson.JsonObject;

public class Presentation extends ModelObjectBase {

	public Presentation(Entity entity) {
		super(entity);
	}

	public static Presentation getById(long id) {
		Presentation presentation = new Presentation(null);
		ModelObjectBase.loadObject(presentation, ENTITY_NAME, id);
		return presentation;
	}
	
	public static Presentation create(JsonObject jsonObject) {
		Entity entity = new Entity(ENTITY_NAME);
		
		entity.setProperty(FIELD_NAME, jsonObject.getAsJsonPrimitive(FIELD_NAME.toLowerCase()).getAsString());
		
		String dateAsString = jsonObject.getAsJsonPrimitive(FIELD_DATE.toLowerCase()).getAsString();
		entity.setProperty(FIELD_DATE, dateAsString);
		
		String author = jsonObject.getAsJsonPrimitive(FIELD_AUTHOR.toLowerCase()).getAsString();
		long authorId = Author.getByName(author, true).getId();
		entity.setProperty(FIELD_AUTHORID, authorId);
		
		int slideCount = jsonObject.getAsJsonPrimitive(FIELD_SLIDECOUNT.toLowerCase()).getAsInt();
		entity.setProperty(FIELD_SLIDECOUNT, slideCount);
		
		Presentation presentation = new Presentation(entity);
		presentation.save();
		return presentation;
	}
	
	public String getName() {
		return (String) m_entity.getProperty(FIELD_NAME);
	}
	
	public LocalDate getDate() {
		String dateAsString = (String) m_entity.getProperty(FIELD_DATE);
		return LocalDate.parse(dateAsString, DateTimeFormatter.ISO_LOCAL_DATE);
	}
	
	public long getSlideCount() {
		return (long) m_entity.getProperty(FIELD_SLIDECOUNT);
	}
	
	public Author getAuthor() {
		long authorId = (long) m_entity.getProperty(FIELD_AUTHORID);
		return Author.getById(authorId);
	}
	
	private static final String ENTITY_NAME = "Presentation";
	private static final String FIELD_NAME = "Name";
	private static final String FIELD_DATE = "Date";
	private static final String FIELD_AUTHOR = "Author";
	private static final String FIELD_AUTHORID = "AuthorId";
	private static final String FIELD_SLIDECOUNT = "SlideCount";
}
