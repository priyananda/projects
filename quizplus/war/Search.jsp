<%@ page import="java.io.*,java.util.*, javax.servlet.*" %>
<%@ page import="us.quizpl.*" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<!-- The HTML 4.01 Transitional DOCTYPE declaration-->
<!-- above set at the top of the file will set     -->
<!-- the browser's rendering engine into           -->
<!-- "Quirks Mode". Replacing this declaration     -->
<!-- with a "Standards Mode" doctype is supported, -->
<!-- but may lead to some differences in layout.   -->

<html>
<head>
<meta http-equiv="content-type" content="text/html; charset=UTF-8">

<link rel="stylesheet" media="screen" href="style.css">
<link rel="stylesheet" type="text/css" href="w2ui-1.4.3.min.css" />
<link rel="stylesheet" href="https://ajax.googleapis.com/ajax/libs/jqueryui/1.11.4/themes/smoothness/jquery-ui.css">
<script	src="http://ajax.googleapis.com/ajax/libs/jquery/2.1.1/jquery.min.js"></script>
<script src="https://ajax.googleapis.com/ajax/libs/jqueryui/1.11.4/jquery-ui.min.js"></script>
<script type="text/javascript" src="w2ui-1.4.3.min.js"></script>

<title>Quiz Plus</title>
</head>

<body>
	<div width="100%" style="background-color: lightgray;" >
	<table>
	<tr> <td> <h1 style="font-size: 30px; margin: 0px; margin-top: 10px; min-height:30px;">Quiz<sup>+</sup></h1>
		 <form action="/search" method="POST"> 
		 <td > <input name="field_text" type="text" maxlength="100" style="width: 450px; font-size: 14px;">
		 <td > <input type="submit" value="Search"></input>
		</form>
	</table>
	</div>
	<div id="searchResultsGrid" style="margin-left: 30px; margin-top: 10px; width: 755px; height: 800px;" />
</body>

<script>
	$('#searchResultsGrid').w2grid({
	    name: 'grid',
	    show: {
	        toolbar: true,
	        footer: true
	    },
	    columns: [
	        { field: 'recid', caption: 'Rank', size: '50px', sortable: true, attr: 'align=center' },
	        { field: 'text', caption: 'Text', size: '450px', sortable: true, resizable: true },
	        { field: 'quiz', caption: 'Quiz', size: '100px', sortable: true, resizable: true },
	        { field: 'author', caption: 'Author', size: '150px', sortable: true, resizable: true }
	    ],
	    searches: [
	        { field: 'quiz', caption: 'Author', type: 'text' },
	        { field: 'author', caption: 'Quiz', type: 'text' },
	    ],
	    sortData: [{ field: 'recid', direction: 'ASC' }],
	    records: [
<%
		SearchArgs args = SearchArgs.fromRequest(request);
		List<SearchResult> results = SearchEngine.doSearch(args);
		boolean first = true;
		for (SearchResult result : results) {
			if (!first) {
%>
			,
<%
			}
%>
			{ recid: '<%= result.getRank() %>', text: '<%= result.getSnippet() %>', quiz: '<%= result.getQuiz() %>',	author: '<%= result.getAuthor() %>' }
<%
		first = false;
		}
%>
	    ]
	});
</script>
