package us.quizpl.model;

import com.google.appengine.api.datastore.DatastoreService;
import com.google.appengine.api.datastore.DatastoreServiceFactory;
import com.google.appengine.api.datastore.Entity;
import com.google.appengine.api.datastore.PreparedQuery;
import com.google.appengine.api.datastore.Query;
import com.google.appengine.api.datastore.Query.FilterOperator;
import com.google.appengine.api.datastore.Query.FilterPredicate;
import com.google.gson.JsonObject;

public class Author extends ModelObjectBase {

	public Author(Entity entity) {
		super(entity);
	}
	
	public static Author getById(long id) {
		Author Author = new Author(null);
		ModelObjectBase.loadObject(Author, ENTITY_NAME, id);
		return Author;
	}
	
	public static Author getByName(String name, boolean fCreate) {
		Query query = new Query(ENTITY_NAME).setFilter(
			new FilterPredicate(FIELD_NAME, FilterOperator.EQUAL, name));
		
	    DatastoreService datastore = DatastoreServiceFactory.getDatastoreService();
	    PreparedQuery pq = datastore.prepare(query);
	    Entity entity = pq.asSingleEntity();
	    if (entity != null)
	    	return new Author(entity);
	    if (!fCreate)
	    	return null;
	    return createByName(name);
  	}
	
	public static Author findByName(String name) {
		return getByName(name, false);
	}
	
	public static Author createByName(String name) {
		Entity entity = new Entity(ENTITY_NAME);
		entity.setProperty(FIELD_NAME, name);
		Author author = new Author(entity);
		author.save();
		return author;
  	}
	
	public static Author create(JsonObject jsonObject) {
		return createByName(jsonObject.getAsJsonPrimitive(FIELD_NAME.toLowerCase()).getAsString());
	}
	
	public String getName() {
		return (String) m_entity.getProperty(FIELD_NAME);
	}
	
	private static final String ENTITY_NAME = "Author";
	private static final String FIELD_NAME = "Name";
}
