package us.quizpl.model;

import java.util.List;

import com.google.appengine.api.search.Document;
import com.google.appengine.api.search.Field;
import com.google.appengine.api.search.ScoredDocument;
import com.google.gson.JsonObject;

import us.quizpl.StorageHelper;
import us.quizpl.search.SearchEngine;

public class Slide {
	
	public Slide(Document doc) {
		m_document = doc;
	}
	
	public static Slide getById(String docId) {
		Document doc = SearchEngine.getIndex().get(docId);
		if (doc == null)
			return null;
		return new Slide(doc);
	}
	
	public static Slide create(JsonObject jsonObject, String authorName) {
		String presId = jsonObject.getAsJsonPrimitive(FIELD_PRESENTATIONID.toLowerCase()).getAsString();
		String imageUrl = jsonObject.getAsJsonPrimitive(FIELD_IMAGEURL.toLowerCase()).getAsString();
		String textContent = jsonObject.getAsJsonPrimitive(FIELD_TEXTCONTENT.toLowerCase()).getAsString();
		String slideIndex = jsonObject.getAsJsonPrimitive(FIELD_SLIDEINDEX.toLowerCase()).getAsString();
		
		imageUrl = StorageHelper.getUrlForGcsFile(BUCKET_NAME, imageUrl);
		if (authorName == null)
			authorName = getAuthorName(presId);
		
		Document doc = Document.newBuilder()
				.addField(Field.newBuilder().setName(FIELD_PRESENTATIONID).setAtom(presId))
				.addField(Field.newBuilder().setName(FIELD_IMAGEURL).setAtom(imageUrl))
				.addField(Field.newBuilder().setName(FIELD_AUTHOR).setAtom(authorName))
				.addField(Field.newBuilder().setName(FIELD_TEXTCONTENT).setText(textContent))
				.addField(Field.newBuilder().setName(FIELD_SLIDEINDEX).setAtom(slideIndex))
				.build();
		SearchEngine.getIndex().put(doc);
		return new Slide(doc);
	}
	
	public Presentation getPresentation() {
		String presIdAsString = m_document.getOnlyField(FIELD_PRESENTATIONID).getAtom();
		long presId = Long.parseLong(presIdAsString);
		return Presentation.getById(presId);
	}
	
	public String getAuthorName() {
		return m_document.getOnlyField(FIELD_AUTHOR).getAtom();
	}
	
	public String getImageUrl() {
		return m_document.getOnlyField(FIELD_IMAGEURL).getAtom();
	}
	
	public String getTextContent() {
		List<Field> fields = ((ScoredDocument) m_document).getExpressions();
		if (fields != null) {
			for (Field field : fields) {
				if (FIELD_TEXTCONTENT.equals(field.getName()))
					return field.getHTML();
			}
		}
		return m_document.getOnlyField(FIELD_TEXTCONTENT).getText();
	}
	
	public String getId() {
		return m_document.getId();
	}
	
	public int getSlideIndex() {
		return Integer.parseInt(m_document.getOnlyField(FIELD_SLIDEINDEX).getAtom());
	}
	
	private static String getAuthorName(String presIdAsString) {
		long presId = Long.parseLong(presIdAsString);
		Presentation pres = Presentation.getById(presId);
		return pres.getAuthor().getName();
	}
	
	private Document m_document;
	public final static String FIELD_PRESENTATIONID = "PresentationId";
	public final static String FIELD_IMAGEURL = "ImageURL";
	public  final static String FIELD_TEXTCONTENT = "TextContent";
	public final static String FIELD_AUTHOR = "Author";
	public final static String FIELD_SLIDEINDEX = "SlideIndex";
	public final static String BUCKET_NAME = "quizplus_storage";
}
