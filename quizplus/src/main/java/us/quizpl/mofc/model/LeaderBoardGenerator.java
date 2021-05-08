package us.quizpl.mofc.model;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import java.util.stream.Collectors;
import java.util.List;

import com.google.appengine.api.datastore.DatastoreService;
import com.google.appengine.api.datastore.DatastoreServiceFactory;
import com.google.appengine.api.datastore.Entity;
import com.google.appengine.api.datastore.Query;
import com.google.gson.JsonArray;
import com.google.gson.JsonObject;

public class LeaderBoardGenerator {
	public static JsonObject getAll() {
		return new LeaderBoardGenerator().compute().toJson();
	}
	
	private static class Score implements Comparable<Score> {
		public String name;
		public int points;
		
		public Score(String name, int points) {
			this.name = name;
			this.points = points;
		}
		
		@Override
		public int compareTo(Score other) {
			return other.points - this.points;
		}
		
		public JsonObject toJson() {
			JsonObject score = new JsonObject();
			score.addProperty("name", this.name);
			score.addProperty("points", this.points);
			return score;
		}
	}
	
	private List<Score> personScores = new ArrayList<>();
	private List<Score> classScores;
	
	private LeaderBoardGenerator compute() {
		Map<Long, Set<String>> personSubmissions = new HashMap<>();
		Map<String, Integer> classNameToPoints = new HashMap<>();
		
		DatastoreService datastore = DatastoreServiceFactory.getDatastoreService();

		Query query = new Query(AnswerSubmission.ENTITY_NAME);
		for (Entity entity : datastore.prepare(query).asIterable()) {
			AnswerSubmission sub = new AnswerSubmission(entity);
			personSubmissions.computeIfAbsent(sub.getPersonId(), pid -> new HashSet<String>());
			personSubmissions.get(sub.getPersonId()).add(sub.getKey());
		}
		
		Query personQuery = new Query(Person.ENTITY_NAME);
		for (Entity entity : datastore.prepare(personQuery).asIterable()) {
			Person person = new Person(entity);
			int points = personSubmissions.getOrDefault(person.getId(), new HashSet<String>())
				.stream()
				.mapToInt(key -> QuestionFactory.get(key).getPoints())
				.sum();
			personScores.add(new Score(person.getName(), points));
			Arrays.stream(person.getClasses()).forEach(className -> {
				classNameToPoints.computeIfAbsent(className, c -> 0);
				classNameToPoints.compute(className, (c, v) -> v + points);
			});
		}
		
		classScores = classNameToPoints.entrySet()
			.stream()
			.map(entry -> new Score(entry.getKey(), entry.getValue()))
			.collect(Collectors.toList());
		Collections.sort(personScores);
		Collections.sort(classScores);
		
		return this;
	}

	private JsonObject toJson() {
		JsonObject json = new JsonObject();
		JsonArray persons = new JsonArray();
		JsonArray classes = new JsonArray();
		personScores.stream().map(Score::toJson).forEach(persons::add);
		classScores.stream().map(Score::toJson).forEach(classes::add);
		json.add("persons", persons);
		json.add("classes", classes);
		return json;
	}
}
