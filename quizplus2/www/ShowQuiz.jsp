<%@ page import="java.io.*,java.util.*, javax.servlet.*" %>
<%@ page import="us.quizpl.*" %>
<%@ page import="us.quizpl.search.*" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>

<html>
<head>
<meta http-equiv="content-type" content="text/html; charset=UTF-8">

<link rel="stylesheet" media="screen" href="style/style.css">
<link rel="stylesheet" type="text/css" href="style/w2ui-1.4.3.min.css" />
<link rel="stylesheet" type="text/css" href="style/jcarousel.connected-carousels.css">
<link rel="stylesheet" href="https://ajax.googleapis.com/ajax/libs/jqueryui/1.11.4/themes/smoothness/jquery-ui.css">

<script	src="http://ajax.googleapis.com/ajax/libs/jquery/2.1.1/jquery.min.js"></script>
<script src="https://ajax.googleapis.com/ajax/libs/jqueryui/1.11.4/jquery-ui.min.js"></script>
<script type="text/javascript" src="scripts/w2ui-1.4.3.min.js"></script>
<script type="text/javascript" src="scripts/jquery.jcarousel.min.js"></script>
<script type="text/javascript" src="scripts/jcarousel.connected-carousels.js"></script>

<title>Quiz Plus</title>
</head>

<%
	QuizResult result = QuizRetriever.find(request);
%>

<body>
<div align="center">
	<h1 style="font-size:40px;"> <%=result.getName()%>
	<h2> <%=result.getAuthor()%>
	<h3> <%=result.getDate()%>
</div>
<div class="connected-carousels">
	<div class="navigation">
		<a href="#" class="prev prev-navigation">&lsaquo;</a>
		<a href="#" class="next next-navigation">&rsaquo;</a>
		<div class="carousel carousel-navigation">
			<ul>
<%
	for(String imageUrl : result.getSlideImageThumbs()) {
%>
				<li><img src="<%=imageUrl%>" alt="" width="100" height="56"></li>
<%
	}
%>			</ul>
		</div>
	</div>
	<div class="stage">
		<div class="carousel carousel-stage">
			<ul>
<%
	for(String imageUrl : result.getSlideImageUrls()) {
%>
				<li><img src="<%=imageUrl%>" width="1024" height="" alt="576"></li>
<%
	}
%>
			</ul>
		</div>
		<a href="#" class="prev prev-stage"><span>&lsaquo;</span></a>
		<a href="#" class="next next-stage"><span>&rsaquo;</span></a>
	</div>
</div>

</body>