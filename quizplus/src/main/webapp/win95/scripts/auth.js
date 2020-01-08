quizRunnerModule
  .factory('AuthState', function($window) {
	  var _currentState = {};
	  _currentState.isLoggedIn = function(){
		  var qsSaved = $window.localStorage.getItem("oauth_access_token");
		  return (qsSaved != null);
	  };
	  return _currentState;
  });