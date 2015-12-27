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

<link rel="stylesheet" media="screen" href="style.css">
<link rel="stylesheet" type="text/css" href="w2ui-1.4.3.min.css" />
<link rel="stylesheet" href="flexslider.css" type="text/css">
<link rel="stylesheet" href="https://ajax.googleapis.com/ajax/libs/jqueryui/1.11.4/themes/smoothness/jquery-ui.css">
<link rel="stylesheet" href="jcarousel.basic.css">

<script	src="http://ajax.googleapis.com/ajax/libs/jquery/2.1.1/jquery.min.js"></script>
<script src="https://ajax.googleapis.com/ajax/libs/jqueryui/1.11.4/jquery-ui.min.js"></script>
<script type="text/javascript" src="w2ui-1.4.3.min.js"></script>
<script type="text/javascript" src="jquery.jcarousel.min.js"></script>
<script type="text/javascript" src="jcarousel.basic.js"></script>

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
  $('.jcarousel')
    .on('jcarousel:createend', function() {
        // Arguments:
        // 1. The method to call
        // 2. The index of the item (note that indexes are 0-based)
        // 3. A flag telling jCarousel jumping to the index without animation
        $(this).jcarousel('scroll', 1, false);
    })
    .jcarousel();
</script>

</body>