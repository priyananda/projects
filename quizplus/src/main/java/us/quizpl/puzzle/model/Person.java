package us.quizpl.puzzle.model;

import java.util.Optional;

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

		Person person = new Person(entity);
		person.save();
		return person;
	}

	public String getName() {
		return (String) m_entity.getProperty(FIELD_NAME);
	}

	public Optional<Long> getLevel() {
		return Optional.ofNullable((Long) m_entity.getProperty(FIELD_LEVEL));
	}

	public Optional<Company> getCompany() {
		return m_entity.hasProperty(FIELD_COMPANY)
				? Optional.of(Company.valueOf((String) m_entity.getProperty(FIELD_LEVEL)))
				: Optional.empty();
	}

	public long getId() {
		return m_entity.getKey().getId();
	}

	public Person setCompanyLevel(CompanyLevel clevel) {
		m_entity.setProperty(FIELD_COMPANY, clevel.getCompany().name());
		m_entity.setProperty(FIELD_LEVEL, (long)clevel.getLevel());
		return this;
	}

	public JsonObject toJson() {
		JsonObject jsonObject = new JsonObject();
		jsonObject.addProperty(FIELD_NAME.toLowerCase(), getName());
		jsonObject.addProperty(FIELD_PID.toLowerCase(), getId());
		getLevel().ifPresent(level -> jsonObject.addProperty(FIELD_LEVEL.toLowerCase(), level));
		getCompany().ifPresent(company -> jsonObject.addProperty(FIELD_COMPANY.toLowerCase(), company.name()));
		return jsonObject;
	}

	public static final String ENTITY_NAME = "Puzzle.Person";
	public static final String FIELD_NAME = "Name";
	public static final String FIELD_PID = "Pid";
	public static final String FIELD_COMPANY = "Company";
	public static final String FIELD_LEVEL = "Level";
}
