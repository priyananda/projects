package us.quizpl.online.model;

import com.google.appengine.api.datastore.DatastoreService;
import com.google.appengine.api.datastore.DatastoreServiceFactory;
import com.google.appengine.api.datastore.Entity;
import com.google.appengine.api.datastore.Query;
import com.google.appengine.api.datastore.Query.FilterOperator;
import com.google.gson.JsonArray;
import com.google.gson.JsonObject;

public class Team {
	public static JsonObject getTeamData(long teamid) {
		JsonObject teamData = new JsonObject();
		teamData.add("members", getTeamMembers(teamid));
		teamData.add("messages", getTeamMessages(teamid));
		return teamData;
	}

	private static JsonArray getTeamMessages(long teamid) {
		JsonArray messages = new JsonArray();
		Channel.getMessages(teamid)
			.stream()
			.map(Message::toJson)
			.forEach(messages::add);
		return messages;
	}

	private static JsonArray getTeamMembers(long teamid) {
		JsonArray members = new JsonArray();
		DatastoreService datastore = DatastoreServiceFactory.getDatastoreService();
		Query query = new Query(Person.ENTITY_NAME)
			.setFilter(
				new Query.FilterPredicate(Person.FIELD_TEAM, FilterOperator.EQUAL, teamid));

		for (Entity entity : datastore.prepare(query).asIterable()) {
			members.add(new Person(entity).toJson());
		}
		return members;
	}
}
