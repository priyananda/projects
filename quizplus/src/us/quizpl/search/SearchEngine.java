package us.quizpl.search;

import java.util.ArrayList;
import java.util.List;

import com.google.appengine.api.search.Index;
import com.google.appengine.api.search.IndexSpec;
import com.google.appengine.api.search.Query;
import com.google.appengine.api.search.QueryOptions;
import com.google.appengine.api.search.Results;
import com.google.appengine.api.search.ScoredDocument;
import com.google.appengine.api.search.SearchServiceFactory;

import us.quizpl.model.Slide;

public class SearchEngine
{
	public static List<SearchResult> doSearch(SearchArgs args) {
		QueryOptions.Builder optionsBuilder = QueryOptions.newBuilder();
		optionsBuilder.setOffset(args.getOffset());
		optionsBuilder.setLimit(args.getLimit());
		if (!args.IsRunningInDevServer())
			optionsBuilder.setFieldsToSnippet(Slide.FIELD_TEXTCONTENT);
		QueryOptions options = optionsBuilder.build();
		
		Query query = Query.newBuilder().setOptions(options).build(args.getSearchText());
		
		Results<ScoredDocument> resultDocs = getIndex().search(query);
		List<SearchResult> results = new ArrayList<SearchResult>();
		for (ScoredDocument scoredDoc : resultDocs) {
			results.add(SearchResult.fromScoredDocument(args, scoredDoc));
		}
		return results;
	}
	
	public static Index getIndex() {
		if (s_index == null) {
			IndexSpec indexSpec = IndexSpec.newBuilder().setName(INDEX_NAME).build(); 
		    s_index = SearchServiceFactory.getSearchService().getIndex(indexSpec);
		}
		return s_index;
	}
	
	private final static String INDEX_NAME = "Slides2";
	
	private static Index s_index;

}
