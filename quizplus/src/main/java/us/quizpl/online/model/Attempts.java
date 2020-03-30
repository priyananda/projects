package us.quizpl.online.model;

import java.util.ArrayList;
import java.util.List;

import com.google.appengine.api.datastore.DatastoreService;
import com.google.appengine.api.datastore.DatastoreServiceFactory;
import com.google.appengine.api.datastore.Entity;
import com.google.appengine.api.datastore.Query;
import com.google.appengine.api.datastore.Query.CompositeFilterOperator;
import com.google.appengine.api.datastore.Query.FilterOperator;
import com.google.appengine.api.datastore.Query.SortDirection;
import com.google.gson.JsonArray;
import com.google.gson.JsonObject;

public class Attempts {
	public static List<AnswerAttempt> getAttempts(long teamId, long questionId) {
		ArrayList<AnswerAttempt> attempts = new ArrayList<>();
		DatastoreService datastore = DatastoreServiceFactory.getDatastoreService();
		Query query = new Query(AnswerAttempt.ENTITY_NAME)
				.setFilter(
					CompositeFilterOperator.and(
						new Query.FilterPredicate(AnswerAttempt.FIELD_TEAM, FilterOperator.EQUAL, teamId),
						new Query.FilterPredicate(AnswerAttempt.FIELD_QUESTION, FilterOperator.EQUAL, questionId)))
				.addSort(AnswerAttempt.FIELD_DATE, SortDirection.DESCENDING);
		
		for (Entity entity : datastore.prepare(query).asIterable()) {
			attempts.add(new AnswerAttempt(entity));
		}
		return attempts;
	}
	
	public static JsonObject getAttemptsAsJson(long teamId, long questionId) {
		JsonArray array = new JsonArray();
		getAttempts(teamId, questionId)
			.stream()
			.map(AnswerAttempt::toJson)
			.forEach(array::add);
		JsonObject json = new JsonObject();
		json.add("answers", array);
		return json;
	}
	
	public static List<String> getLatestAnswers(long teamId){
		ArrayList<String> latestAnswers = new ArrayList<>();
		DatastoreService datastore = DatastoreServiceFactory.getDatastoreService();
		Query query = new Query(AnswerAttempt.ENTITY_NAME)
			.setFilter(new Query.FilterPredicate(AnswerAttempt.FIELD_TEAM, FilterOperator.EQUAL, teamId))
			.addSort(AnswerAttempt.FIELD_QUESTION, SortDirection.ASCENDING)
			.addSort(AnswerAttempt.FIELD_DATE, SortDirection.ASCENDING);
		for (Entity entity : datastore.prepare(query).asIterable()) {
			AnswerAttempt attempt = new AnswerAttempt(entity);
			while (latestAnswers.size() != attempt.getQuestion()) {
				latestAnswers.add("");
			}
			latestAnswers.set((int)attempt.getQuestion(), attempt.getText());
		}
		return latestAnswers;
	}
}
