package us.quizpl.model;

import com.google.appengine.api.search.Document;
import com.google.appengine.api.search.Field;
import com.google.appengine.api.search.Index;
import com.google.appengine.api.search.IndexSpec;
import com.google.appengine.api.search.SearchServiceFactory;
import com.google.gson.JsonObject;

public class Slide {
	
	public Slide(Document doc) {
		m_document = doc;
	}
	
	public static Slide getById(String docId) {
		Document doc = getIndex().get(docId);
		if (doc == null)
			return null;
		return new Slide(doc);
	}
	
	public static Slide create(JsonObject jsonObject) {
		String presId = jsonObject.getAsJsonPrimitive(FIELD_PRESENTATIONID.toLowerCase()).getAsString();
		String imageUrl = jsonObject.getAsJsonPrimitive(FIELD_IMAGEURL.toLowerCase()).getAsString();
		String textContent = jsonObject.getAsJsonPrimitive(FIELD_TEXTCONTENT.toLowerCase()).getAsString();
		
		Document doc = Document.newBuilder()
				.addField(Field.newBuilder().setName(FIELD_PRESENTATIONID).setAtom(presId))
				.addField(Field.newBuilder().setName(FIELD_IMAGEURL).setAtom(imageUrl))
				.addField(Field.newBuilder().setName(FIELD_TEXTCONTENT).setText(textContent))
				.build();
		getIndex().put(doc);
		return new Slide(doc);
	}
	
	public Presentation getPresentation() {
		String presIdAsString = m_document.getOnlyField(FIELD_PRESENTATIONID).getAtom();
		long presId = Long.parseLong(presIdAsString);
		return Presentation.getById(presId);
	}
	
	public String getId() {
		return m_document.getId();
	}
	
	private static Index getIndex() {
		if (s_index == null) {
			IndexSpec indexSpec = IndexSpec.newBuilder().setName(INDEX_NAME).build(); 
		    s_index = SearchServiceFactory.getSearchService().getIndex(indexSpec);
		}
		return s_index;
	}
	
	private Document m_document;
	private static Index s_index;
	private final static String INDEX_NAME = "Slides";
	private final static String FIELD_PRESENTATIONID = "PresentationId";
	private final static String FIELD_IMAGEURL = "ImageURL";
	private final static String FIELD_TEXTCONTENT = "TextContent";
}
