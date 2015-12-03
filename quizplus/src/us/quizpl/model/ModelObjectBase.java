package us.quizpl.model;

import com.google.appengine.api.datastore.DatastoreService;
import com.google.appengine.api.datastore.DatastoreServiceFactory;
import com.google.appengine.api.datastore.Entity;
import com.google.appengine.api.datastore.Key;
import com.google.appengine.api.datastore.KeyFactory;

public class ModelObjectBase {
	
	public ModelObjectBase(Entity entity) {
		m_entity = entity;
	}
	
	public static void loadObject(ModelObjectBase modelObj, String entityName, long id) {
		try {
			DatastoreService datastore = DatastoreServiceFactory.getDatastoreService();
			Key key = KeyFactory.createKey(entityName, id);
			modelObj.m_entity = datastore.get(key);
		} catch(Exception e) { }
	}
	
	public void save() {
		DatastoreService datastore = DatastoreServiceFactory.getDatastoreService();
		datastore.put(m_entity);
	}
	
	public long getId() {
		return m_entity.getKey().getId();
	}

	protected Entity m_entity;
}
