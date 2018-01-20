<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>

<html>

<div id="message_placeholder">
</div>

<script>
	window.localStorage.setItem("oauth_access_token", "1");
	document.getElementById("message_placeholder").innerHTML = "<b>Authorized!</b>";
</script>

</html>