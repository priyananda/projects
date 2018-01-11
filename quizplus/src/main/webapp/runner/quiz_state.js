quizRunnerModule
  .factory('QuizState', function($http) {
	 var _currentState = {};
	 var _teamScores = [
		{name: "Team 1", points: 0},
		{name: "Team 2", points: 0},
		{name: "Team 3", points: 0},
		{name: "Team 4", points: 0},
		{name: "Team 5", points: 0},
		{name: "Team 6", points: 0}
	  ];

	 var _questionClosed = [];
	 for (i = 0; i < questionInfo.lenght; ++i)
		 _questionClosed.push(false);
	 
	 _currentState.getTeamScores = function() {
		 return _teamScores;
	 }
	 
	 _currentState.isQuestionClosed = function(qid) {
		 return _questionClosed[qid - 1];
	 }
	 
	 _currentState.closeQuestion = function(qid) {
		 _questionClosed[qid - 1] = true;
	 }
	 
	 return _currentState;
  })