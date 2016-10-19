package us.quizpl.app.model;

import java.util.ArrayList;

import com.google.appengine.api.datastore.DatastoreService;
import com.google.appengine.api.datastore.DatastoreServiceFactory;
import com.google.appengine.api.datastore.Entity;
import com.google.appengine.api.datastore.Key;
import com.google.appengine.api.datastore.KeyFactory;
import com.google.appengine.api.datastore.PreparedQuery;
import com.google.appengine.api.datastore.Query;
import com.google.appengine.api.datastore.Query.SortDirection;
import com.google.gson.JsonObject;

import us.quizpl.model.ModelObjectBase;

public class Finalist extends ModelObjectBase {
	public Finalist(Entity entity) {
		super(entity);
	}
	
	public String getFirstPersonName() {
		return (String) m_entity.getProperty(FIELD_FIRST_PERSON);
	}
	public void setFirstPersonName(String firstPersonName) {
		m_entity.setProperty(FIELD_FIRST_PERSON, firstPersonName);
	}
	public String getSecondPersonName() {
		return (String) m_entity.getProperty(FIELD_SECOND_PERSON);
	}
	public void setSecondPersonName(String secondPersonName) {
		m_entity.setProperty(FIELD_SECOND_PERSON, secondPersonName);
	}
	public long getScore() {
		return (long) m_entity.getProperty(FIELD_SCORE);
	}
	public void setScore(long score) {
		m_entity.setProperty(FIELD_SCORE, score);
	}
	
	public static Finalist getOrCreateFromJson(JsonObject jsonObject) {
		long teamId = jsonObject.getAsJsonPrimitive(FIELD_TEAM_ID.toLowerCase()).getAsLong();
		Finalist teamInfo = getOrCreate(teamId);
		
		teamInfo.setFirstPersonName(jsonObject.getAsJsonPrimitive(FIELD_FIRST_PERSON.toLowerCase()).getAsString());
		teamInfo.setSecondPersonName(jsonObject.getAsJsonPrimitive(FIELD_SECOND_PERSON.toLowerCase()).getAsString());
		teamInfo.setScore(jsonObject.getAsJsonPrimitive(FIELD_SCORE.toLowerCase()).getAsLong());
		
		teamInfo.save();
		return teamInfo;
	}
	
	public JsonObject toJsonObject(){
		JsonObject jsonObject = new JsonObject();
		jsonObject.addProperty(FIELD_TEAM_ID.toLowerCase(), getId());
		jsonObject.addProperty(FIELD_FIRST_PERSON.toLowerCase(), getFirstPersonName());
		jsonObject.addProperty(FIELD_SECOND_PERSON.toLowerCase(), getSecondPersonName());
		jsonObject.addProperty(FIELD_SCORE.toLowerCase(), getScore());
		return jsonObject;
	}
	
	public static Finalist getOrCreate(long id){
		Finalist teamInfo = new Finalist(null);
		ModelObjectBase.loadObject(teamInfo, ENTITY_NAME, id);
		if (teamInfo.m_entity != null)
			return teamInfo;
		
		Key key = KeyFactory.createKey(ENTITY_NAME, id);
		teamInfo.m_entity = new Entity(key);
		teamInfo.save();
		
		return teamInfo;
	}
	
	public static ArrayList<Finalist> getAllTeams() {
		ArrayList<Finalist> teams = new ArrayList<Finalist>();
		
		Query query = new Query(ENTITY_NAME);
		DatastoreService datastore = DatastoreServiceFactory.getDatastoreService();
		query.addSort(FIELD_SCORE, SortDirection.DESCENDING);
	    PreparedQuery pq = datastore.prepare(query);
	    for (Entity entity : pq.asIterable()) {
	    	teams.add(new Finalist(entity));
		}
	    
	    return teams;
	}
	
	private static String ENTITY_NAME         = "Finalist";
	private static String FIELD_TEAM_ID       = "TeamId";
	private static String FIELD_FIRST_PERSON  = "FirstPersonName";
	private static String FIELD_SECOND_PERSON = "SecondPersonName";
	private static String FIELD_SCORE         = "Score";
}
