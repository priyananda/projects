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
<link rel="stylesheet" type="text/css" href="style/flexslider.css">
<link rel="stylesheet" href="style/jcarousel.basic.css">
<link rel="stylesheet" href="https://ajax.googleapis.com/ajax/libs/jqueryui/1.11.4/themes/smoothness/jquery-ui.css">

<script	src="http://ajax.googleapis.com/ajax/libs/jquery/2.1.1/jquery.min.js"></script>
<script src="https://ajax.googleapis.com/ajax/libs/jqueryui/1.11.4/jquery-ui.min.js"></script>
<script type="text/javascript" src="scripts/w2ui-1.4.3.min.js"></script>
<script type="text/javascript" src="scripts/jquery.jcarousel.min.js"></script>
<script type="text/javascript" src="scripts/jcarousel.basic.js"></script>

<title>Quiz Plus</title>

</head>

<body>

<div class="jcarousel-wrapper">
 <div class="jcarousel">
  <ul class="slides">
<%
 	ArrayList<String> images = SlideRetriever.getSlideAndNeighbours(request);
 	for(String imageUrl : images ) { 
%>
    <li>
      <img src="<%=imageUrl%>" width="700"/>
    </li>
<%
	}
%>
  </ul>
 </div>
 
 <a href="#" class="jcarousel-control-prev">&lsaquo;</a>
 <a href="#" class="jcarousel-control-next">&rsaquo;</a>
 <p class="jcarousel-pagination"></p>
</div>

<script>
	$(window).load(function(){
	    $('.jcarousel').jcarousel('scroll', 1, false);
	});
</script>

</body>