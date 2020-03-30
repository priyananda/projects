package us.quizpl.online.model;

import java.util.ArrayList;
import java.util.List;

import com.google.appengine.api.datastore.DatastoreService;
import com.google.appengine.api.datastore.DatastoreServiceFactory;
import com.google.appengine.api.datastore.Entity;
import com.google.appengine.api.datastore.Query;
import com.google.appengine.api.datastore.Query.FilterOperator;
import com.google.appengine.api.datastore.Query.SortDirection;

public class Channel {
	public static List<Message> getMessages(long channel) {
		ArrayList<Message> messages = new ArrayList<>();
		DatastoreService datastore = DatastoreServiceFactory.getDatastoreService();
		Query query = new Query(Message.ENTITY_NAME)
				.setFilter(new Query.FilterPredicate(Message.FIELD_CHANNEL, FilterOperator.EQUAL, channel))
				.addSort(Message.FIELD_DATE, SortDirection.ASCENDING);
		
		for (Entity entity : datastore.prepare(query).asIterable()) {
			messages.add(new Message(entity));
		}
		return messages;
	}
}
