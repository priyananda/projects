<%@ page import="java.io.*,java.util.*, javax.servlet.*" %>
<%@ page import="us.quizpl.*" %>
<%@ page import="us.quizpl.search.*" %>
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

<link rel="stylesheet" media="screen" href="style/style.css">
<link rel="stylesheet" type="text/css" href="style/w2ui-1.4.3.min.css" />
<link rel="stylesheet" href="https://ajax.googleapis.com/ajax/libs/jqueryui/1.11.4/themes/smoothness/jquery-ui.css">

<script	src="http://ajax.googleapis.com/ajax/libs/jquery/2.1.1/jquery.min.js"></script>
<script src="https://ajax.googleapis.com/ajax/libs/jqueryui/1.11.4/jquery-ui.min.js"></script>
<script type="text/javascript" src="scripts/w2ui-1.4.3.min.js"></script>

<title>Quiz Plus</title>
</head>

<%
	SearchArgs args = SearchArgs.fromRequest(request);
%>	

<body>
	<div style="width: 100%; height:800px;" id="layout">;

		<div width="100%" style="background-color: lightgray;" id="topPane">
            <form action="/Search.jsp" method="GET">
			<table>
			 <tr> <td> <h1 style="font-size: 30px; margin: 0px; margin-top: 10px; min-height:30px;">Quiz<sup>+</sup></h1>
			 	<td > <input name="field_search_text" type="text" maxlength="100" style="width: 450px; font-size: 14px;" value='<%= args.getSearchText() %>'>
			 	<td > <input type="submit" value="Search"></input>
			</table>
			</form>
		</div>
		
		<div id="searchResultsGrid" style="margin-left: 30px; margin-top: 10px; width: 755px; height: 800px;" />
	
</body>

<script>
	var slideIds = new Array("");
<%
	List<SearchResult> results = SearchEngine.doSearch(args);
	for (SearchResult result : results) {
%>	
	slideIds.push('<%=result.getId()%>');
<%
	}
%>
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
		boolean first = true;
		int index = 1;
		for (SearchResult result : results) {
			if (!first) {
%>
			,
<%
			}
%>
			{ recid: '<%= index %>', text: '<%= result.getSnippet() %>', quiz: '<%= result.getQuiz() %>',	author: '<b><%= result.getAuthor() %></b>' }
<%
		first = false;
		++index;
		}
%>
	    ],
	    onSelect: function(event) {
	    	//w2ui['layout'].load('main', '/Slide.jsp?slideid=' + slideIds[event.recid]);
	    	var iframeElement = document.getElementById('slideFrame');
	    	iframeElement.src = '/Slide.jsp?slideid=' + slideIds[event.recid];
    	}        
	});
	
	var pstyle = 'background-color: #F5F6F7; border: 1px solid #dfdfdf; padding: 5px;';
    $('#layout').w2layout({
        name: 'layout',
        panels: [
            { type: 'top',  size: 90, resizable: true, style: pstyle, content: $('#topPane').html() },
            { type: 'left', size: 755, resizable: true, style: pstyle, content: w2ui['grid'] },
            { type: 'main', style: pstyle, content:  '<iframe src=\"\" id=\"slideFrame\" width=\"960\" height=\"720\" />' }
        ]
    });
</script>
