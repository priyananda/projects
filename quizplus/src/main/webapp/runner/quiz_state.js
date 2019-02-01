quizRunnerModule
  .factory('QuizState', function($http, $window) {
	 var _currentState = {};
	 var _teamScores = [];
	 var _questionClosed = [];
	 var _graph = null;

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
	 
	 _currentState.getGraph = function() {
		 return _graph;
	 };

	 _currentState.setGraph = function(graph) {
		 _graph = graph;
	 };
	 
	 _currentState.loadFromLocalStorage = function() {
		 var tsSaved = $window.localStorage.getItem('quiz222-team-scores');
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
		 var qsSaved = $window.localStorage.getItem('quiz222-questions-closed');
		 if (qsSaved != null) {
			 _questionClosed = JSON.parse(qsSaved);
		 } else if (questionInfo !== undefined){
			 _questionClosed = [];
			 for (i = 0; i < questionInfo.length; ++i)
				 _questionClosed.push(false);
		 }
	 };
	 
	 _currentState.saveToLocalStorage = function() {
		 $window.localStorage.setItem('quiz222-team-scores', JSON.stringify(_teamScores));
		 $window.localStorage.setItem('quiz222-questions-closed', JSON.stringify(_questionClosed));
	 };
	 
	 _currentState.loadFromLocalStorage();
	 return _currentState;
  });