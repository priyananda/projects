package us.quizpl;

import java.util.ArrayList;
import java.util.List;

import com.google.appengine.api.search.Query;
import com.google.appengine.api.search.QueryOptions;
import com.google.appengine.api.search.Results;
import com.google.appengine.api.search.ScoredDocument;

import us.quizpl.model.Slide;

public class SearchEngine
{
	public static List<SearchResult> doSearch(SearchArgs args) {
		QueryOptions.Builder optionsBuilder = QueryOptions.newBuilder();
		optionsBuilder.setOffset(args.getOffset());
		optionsBuilder.setLimit(args.getLimit());
		if (!IS_RUNNING_IN_DEV_SERVER)
			optionsBuilder.setFieldsToSnippet(Slide.FIELD_TEXTCONTENT);
		QueryOptions options = optionsBuilder.build();
		
		Query query = Query.newBuilder().setOptions(options).build(args.getSearchText());
		
		Results<ScoredDocument> resultDocs = Slide.getIndex().search(query);
		List<SearchResult> results = new ArrayList<SearchResult>();
		for (ScoredDocument scoredDoc : resultDocs) {
			results.add(SearchResult.fromScoredDocument(scoredDoc));
		}
		return results;
	}
	
	private static final boolean IS_RUNNING_IN_DEV_SERVER = true;
}
