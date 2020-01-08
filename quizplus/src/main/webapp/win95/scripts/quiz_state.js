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
	 
	 _currentState.addToAllTeams = function(delta) {
		 _teamScores.forEach(function(score) {
			if (score.points + delta < 0)
				score.points = 0;
			else
				score.points += delta;
		 });
	 };
	 
	 _currentState.getGraph = function() {
		 return _graph;
	 };

	 _currentState.setGraph = function(graph) {
		 _graph = graph;
	 };
	 
	 _currentState.loadFromLocalStorage = function() {
		 var tsSaved = $window.localStorage.getItem('win95-team-scores');
		 if (tsSaved != null) {
			 _teamScores = JSON.parse(tsSaved);
		 } else {
			 _teamScores = [
				{name: "Team1.txt", points: 0},
				{name: "Team2.txt", points: 0},
				{name: "Team3.txt", points: 0},
				{name: "Team4.txt", points: 0},
				{name: "Team5.txt", points: 0},
				{name: "Team6.txt", points: 0}
			  ];
		 }
		 var qsSaved = $window.localStorage.getItem('win95-questions-closed');
		 if (qsSaved != null) {
			 _questionClosed = JSON.parse(qsSaved);
		 } else if (questionInfo !== undefined){
			 _questionClosed = [];
			 for (i = 0; i < questionInfo.length; ++i)
				 _questionClosed.push(false);
		 }
	 };
	 
	 _currentState.saveToLocalStorage = function() {
		 $window.localStorage.setItem('win95-team-scores', JSON.stringify(_teamScores));
		 $window.localStorage.setItem('win95-questions-closed', JSON.stringify(_questionClosed));
	 };
	 
	 _currentState.loadFromLocalStorage();
	 return _currentState;
  });