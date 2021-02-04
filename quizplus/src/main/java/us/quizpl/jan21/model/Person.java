package us.quizpl.jan21.model;

import com.google.appengine.api.datastore.DatastoreService;
import com.google.appengine.api.datastore.DatastoreServiceFactory;
import com.google.appengine.api.datastore.Entity;
import com.google.appengine.api.datastore.FetchOptions;
import com.google.appengine.api.datastore.Query;
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
	
	public static Person create(String name) {
		Entity entity = new Entity(ENTITY_NAME);
		
		entity.setProperty(FIELD_NAME, name);
		entity.setProperty(FIELD_TEAM, assignTeam());
		
		Person person = new Person(entity);
		person.save();
		return person;
	}
	
	private static long assignTeam() {
		DatastoreService datastore = DatastoreServiceFactory.getDatastoreService();
		Query query = new Query(ENTITY_NAME).setKeysOnly();
		int personCount = datastore.prepare(query).countEntities(FetchOptions.Builder.withDefaults()) - 1;
		return (personCount % 6) + 1;
	}
	
	public String getName() {
		return (String) m_entity.getProperty(FIELD_NAME);
	}
	
	public long getTeam() {
		return (long) m_entity.getProperty(FIELD_TEAM);
	}
	
	public long getId() {
		return m_entity.getKey().getId();
	}
	
	public JsonObject toJson() {
		JsonObject jsonObject = new JsonObject();
		jsonObject.addProperty(FIELD_NAME.toLowerCase(), getName());
		jsonObject.addProperty(FIELD_TEAM.toLowerCase(), getTeam());
		jsonObject.addProperty(FIELD_PID.toLowerCase(), getId());
		return jsonObject;
	}
	
	public static final String ENTITY_NAME = "Jan21.Person";
	public static final String FIELD_NAME = "Name";
	public static final String FIELD_TEAM= "Team";
	public static final String FIELD_PID = "Pid";
}
