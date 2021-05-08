package us.quizpl.mofc.model;

import java.util.Arrays;
import com.google.appengine.api.datastore.Entity;
import com.google.gson.JsonArray;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;

import us.quizpl.model.ModelObjectBase;

public class Person extends ModelObjectBase {
	public Person(Entity entity) {
		super(entity);
	}

	public static Person getById(long id) {
		Person person = new Person(null);
		ModelObjectBase.loadObject(person, ENTITY_NAME, id);
		return person;
	}

	public static Person create(String name, String classes) {
		Entity entity = new Entity(ENTITY_NAME);

		entity.setProperty(FIELD_NAME, name);
		if (classes != null)
			entity.setProperty(FIELD_CLASSES, classes);

		Person person = new Person(entity);
		person.save();
		return person;
	}

	public String getName() {
		return (String) m_entity.getProperty(FIELD_NAME);
	}

	public long getId() {
		return m_entity.getKey().getId();
	}
	
	public String[] getClasses() {
		String classesAsString = (String)m_entity.getProperty(FIELD_CLASSES);
		if (classesAsString == null || classesAsString.isEmpty())
			return new String[] {};
		return classesAsString.split(",");
	}

	public JsonObject toJson() {
		JsonObject jsonObject = new JsonObject();
		jsonObject.addProperty(FIELD_NAME.toLowerCase(), getName());
		jsonObject.addProperty(FIELD_PID.toLowerCase(), getId());
		jsonObject.add(FIELD_CLASSES.toLowerCase(), toJsonArray(getClasses()));
		return jsonObject;
	}

	private JsonElement toJsonArray(String[] classes) {
		JsonArray array = new JsonArray();
	    Arrays.stream(classes).forEach(array::add);
		return array;
	}

	public static final String ENTITY_NAME = "Mofc.Person";
	public static final String FIELD_NAME = "Name";
	public static final String FIELD_PID = "Pid";
	public static final String FIELD_CLASSES = "Classes";
}
