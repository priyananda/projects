package us.quizpl.app.model;

import java.util.ArrayList;

import com.google.appengine.api.datastore.DatastoreService;
import com.google.appengine.api.datastore.DatastoreServiceFactory;
import com.google.appengine.api.datastore.Entity;
import com.google.appengine.api.datastore.Key;
import com.google.appengine.api.datastore.KeyFactory;
import com.google.appengine.api.datastore.PreparedQuery;
import com.google.appengine.api.datastore.Query;
import com.google.gson.JsonObject;

import us.quizpl.model.ModelObjectBase;

public class TeamInfo extends ModelObjectBase {
	public TeamInfo(Entity entity) {
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
	public boolean isFinalist() {
		return (boolean) m_entity.getProperty(FIELD_IS_FINALIST);
	}
	public void setFinalist(boolean isFinalist) {
		m_entity.setProperty(FIELD_IS_FINALIST, isFinalist);
	}
	
	public static TeamInfo getOrCreateFromJson(JsonObject jsonObject) {
		long teamId = jsonObject.getAsJsonPrimitive(FIELD_TEAM_ID.toLowerCase()).getAsLong();
		TeamInfo teamInfo = getOrCreate(teamId);
		
		teamInfo.setFirstPersonName(jsonObject.getAsJsonPrimitive(FIELD_FIRST_PERSON.toLowerCase()).getAsString());
		teamInfo.setSecondPersonName(jsonObject.getAsJsonPrimitive(FIELD_SECOND_PERSON.toLowerCase()).getAsString());
		teamInfo.setFinalist(jsonObject.getAsJsonPrimitive(FIELD_IS_FINALIST.toLowerCase()).getAsBoolean());
		
		teamInfo.save();
		return teamInfo;
	}
	
	public JsonObject toJsonObject(){
		JsonObject jsonObject = new JsonObject();
		jsonObject.addProperty(FIELD_TEAM_ID.toLowerCase(), getId());
		jsonObject.addProperty(FIELD_FIRST_PERSON.toLowerCase(), getFirstPersonName());
		jsonObject.addProperty(FIELD_SECOND_PERSON.toLowerCase(), getSecondPersonName());
		jsonObject.addProperty(FIELD_IS_FINALIST.toLowerCase(), isFinalist());
		return jsonObject;
	}
	
	public static TeamInfo getOrCreate(long id){
		TeamInfo teamInfo = new TeamInfo(null);
		ModelObjectBase.loadObject(teamInfo, ENTITY_NAME, id);
		if (teamInfo.m_entity != null)
			return teamInfo;
		
		Key key = KeyFactory.createKey(ENTITY_NAME, id);
		teamInfo.m_entity = new Entity(key);
		teamInfo.save();
		
		return teamInfo;
	}
	
	public static ArrayList<TeamInfo> getAllTeams() {
		ArrayList<TeamInfo> teams = new ArrayList<TeamInfo>();
		
		Query query = new Query(ENTITY_NAME);
		DatastoreService datastore = DatastoreServiceFactory.getDatastoreService();
	    PreparedQuery pq = datastore.prepare(query);
	    for (Entity entity : pq.asIterable()) {
	    	teams.add(new TeamInfo(entity));
		}
	    
	    return teams;
	}
	
	private static String ENTITY_NAME         = "TeamInfo";
	private static String FIELD_TEAM_ID       = "TeamId";
	private static String FIELD_FIRST_PERSON  = "FirstPersonName";
	private static String FIELD_SECOND_PERSON = "SecondPersonName";
	private static String FIELD_IS_FINALIST   = "IsFinalist";
}
