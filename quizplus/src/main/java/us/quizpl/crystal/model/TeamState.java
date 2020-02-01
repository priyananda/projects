package us.quizpl.crystal.model;

import com.google.appengine.api.datastore.DatastoreService;
import com.google.appengine.api.datastore.DatastoreServiceFactory;
import com.google.appengine.api.datastore.Entity;
import com.google.appengine.api.datastore.PreparedQuery;
import com.google.appengine.api.datastore.Query;
import com.google.appengine.api.datastore.Query.FilterOperator;
import com.google.appengine.api.datastore.Query.FilterPredicate;

import us.quizpl.model.ModelObjectBase;

public class TeamState extends ModelObjectBase {
	public static class QuestionState {
		public boolean isAnswered = false;
		public long pointsAwarded = 0;
	}
	public static enum QuestionCategory {
		PHYSICAL,
		MENTAL,
		MYSTERY,
		SKILL
	};
	
	private TeamState(Entity entity) {
		super(entity);
	}
	
	public static TeamState getOrCreate(long teamId) {
		Query query = new Query(ENTITY_NAME).setFilter(
				new FilterPredicate(FIELD_TEAM_ID, FilterOperator.EQUAL, teamId));
			
	    DatastoreService datastore = DatastoreServiceFactory.getDatastoreService();
	    PreparedQuery pq = datastore.prepare(query);
	    Entity entity = pq.asSingleEntity();
	    if (entity != null)
	    	return new TeamState(entity);
	    return create(teamId);
	}
	
	public long getTeamId() {
		return (Long)m_entity.getProperty(FIELD_TEAM_ID);
	}
	
	public QuestionState getQuestionState(QuestionCategory cat) {
		switch(cat) {
			case PHYSICAL:
				return getState(FIELD_Q1_IS_ANSWERED, FIELD_Q1_POINTS);
			case MENTAL:
				return getState(FIELD_Q2_IS_ANSWERED, FIELD_Q2_POINTS);
			case MYSTERY:
				return getState(FIELD_Q3_IS_ANSWERED, FIELD_Q3_POINTS);
			case SKILL:
				return getState(FIELD_Q4_IS_ANSWERED, FIELD_Q4_POINTS);
		}
		return null;
	}
	
	public void answerQuestion(QuestionCategory cat, long points) {
		switch(cat) {
			case PHYSICAL:
				setState(FIELD_Q1_IS_ANSWERED, FIELD_Q1_POINTS, points);
				break;
			case MENTAL:
				setState(FIELD_Q2_IS_ANSWERED, FIELD_Q2_POINTS, points);
				break;
			case MYSTERY:
				setState(FIELD_Q3_IS_ANSWERED, FIELD_Q3_POINTS, points);
				break;
			case SKILL:
				setState(FIELD_Q4_IS_ANSWERED, FIELD_Q4_POINTS, points);
				break;
		}
	}
	
	private QuestionState getState(String isAnsweredField, String pointsField) {
		QuestionState state = new QuestionState();
		state.isAnswered = (Boolean)m_entity.getProperty(isAnsweredField);
		state.pointsAwarded = (Long)m_entity.getProperty(pointsField);
		return state;
	}
	private void setState(String isAnsweredField, String pointsField, long points) {
		m_entity.setProperty(isAnsweredField, Boolean.TRUE);
		m_entity.setProperty(pointsField, Long.valueOf(points));
	}
	
	private static TeamState create(long teamId) {
		Entity entity = new Entity(ENTITY_NAME);
		entity.setProperty(FIELD_TEAM_ID, teamId);
		entity.setProperty(FIELD_Q1_IS_ANSWERED, Boolean.FALSE);
		entity.setProperty(FIELD_Q1_POINTS, Long.valueOf(0));
		entity.setProperty(FIELD_Q2_IS_ANSWERED, Boolean.FALSE);
		entity.setProperty(FIELD_Q2_POINTS, Long.valueOf(0));
		entity.setProperty(FIELD_Q3_IS_ANSWERED, Boolean.FALSE);
		entity.setProperty(FIELD_Q3_POINTS, Long.valueOf(0));
		entity.setProperty(FIELD_Q4_IS_ANSWERED, Boolean.FALSE);
		entity.setProperty(FIELD_Q4_POINTS, Long.valueOf(0));
		TeamState team = new TeamState(entity);
		team.save();
		return team;
	}
	
	private static final String ENTITY_NAME = "CrystalTeamState";
	private static final String FIELD_TEAM_ID = "TeamId";
	private static final String FIELD_Q1_IS_ANSWERED = "Q1IsAnswered";
	private static final String FIELD_Q1_POINTS = "Q1Points";
	private static final String FIELD_Q2_IS_ANSWERED = "Q2IsAnswered";
	private static final String FIELD_Q2_POINTS = "Q2Points";
	private static final String FIELD_Q3_IS_ANSWERED = "Q3IsAnswered";
	private static final String FIELD_Q3_POINTS = "Q3Points";
	private static final String FIELD_Q4_IS_ANSWERED = "Q4IsAnswered";
	private static final String FIELD_Q4_POINTS = "Q4Points";
}
