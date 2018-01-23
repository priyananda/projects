quizRunnerModule
  .factory('QuizState', function($http, $window) {
	 var _currentState = {};
	 var _teamScores = [];
	 var _questionClosed = [];
	 
	 _currentState.getTeamScores = function() {
		 return _teamScores;
	 };
	 
	 _currentState.isQuestionClosed = function(qid) {
		 return _questionClosed[qid - 1];
	 };
	 
	 _currentState.closeQuestion = function(qid) {
		 _questionClosed[qid - 1] = true;
		 _currentState.saveToLocalStorage();
	 };
	 
	 _currentState.clearLocalStorage = function() {
		 $window.localStorage.clear();
	 };
	 
	 _currentState.loadFromLocalStorage = function() {
		 var tsSaved = $window.localStorage.getItem('quiz219-team-scores');
		 if (tsSaved != null) {
			 _teamScores = JSON.parse(tsSaved);
		 } else {
			 _teamScores = [
				{name: "T1", points: 0},
				{name: "T2", points: 0},
				{name: "T3", points: 0},
				{name: "T4", points: 0},
				{name: "T5", points: 0},
				{name: "T6", points: 0}
			  ];
		 }
		 var qsSaved = $window.localStorage.getItem('quiz219-questions-closed');
		 if (qsSaved != null) {
			 _questionClosed = JSON.parse(qsSaved);
		 } else {
			 _questionClosed = [];
			 for (i = 0; i < questionInfo.length; ++i)
				 _questionClosed.push(false);
		 }
	 };
	 
	 _currentState.saveToLocalStorage = function() {
		 $window.localStorage.setItem('quiz219-team-scores', JSON.stringify(_teamScores));
		 $window.localStorage.setItem('quiz219-questions-closed', JSON.stringify(_questionClosed));
	 };
	 
	 _currentState.loadFromLocalStorage();
	 return _currentState;
  });