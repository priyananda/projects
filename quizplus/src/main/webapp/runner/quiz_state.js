quizRunnerModule
  .factory('QuizState', function($http, $window) {
	 var _currentState = {};
	 var _teamScores = [];
	 var _questionClosed = [];
	 var _r1state = {start: 1, end: 15};
	 var _r2state = new Set();
	 var _r3state = new Set();
	 
	 _currentState.getTeamScores = function() {
		 return _teamScores;
	 };
	 
	 _currentState.isQuestionClosed = function(qid) {
		 return _questionClosed[qid - 1];
	 };
	 
	 _currentState.closeQuestion = function(qid) {
		 _questionClosed[qid - 1] = true;
		 if (qid == _r1state.start) {
			 _r1state.start++;
		 }
		 if (qid == _r1state.end) {
			 _r1state.end--;
		 }
		 if (_r2state.stack.length > 0 && _r2state.stack[_r2state.stack.length - 1] == qid) {
			 _r2state.stack.pop();
		 }
		 if (qid >= 28 && qid <= 33) {
			 _r3state.add(qid);
		 }
		 _currentState.saveToLocalStorage();
	 };
	 
	 _currentState.clearLocalStorage = function() {
		 $window.localStorage.clear();
	 };
	 
	 _currentState.getR1State = function() {
		 return _r1state;
	 };
	 
	 _currentState.getR2State = function() {
		 return _r2state;
	 };
	 
	 _currentState.pushTopicToStack = function(topicIdx) {
		 _r2state.stack = _r2state.stack.concat(r2topics[topicIdx].qids);
		 _r2state.usedTopics.add(topicIdx);
	 };
	 
	 _currentState.getR3State = function() {
		 return _r3state;
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
		 var r1state = $window.localStorage.getItem('quiz222-r1state');
		 if (r1state != null) {
			 _r1state = JSON.parse(r1state);
		 } else {
			 _r1state = {start: 1, end: 15};
		 }
		 var r2state = $window.localStorage.getItem('quiz222-r2state');
		 if (r2state != null) {
			 _r2state = JSON.parse(r2state);
			 _r2state.usedTopics = new Set(_r2state.usedTopics);
		 } else {
			 _r2state = {usedTopics: new Set(), stack: []};
		 }
		 var r3state = $window.localStorage.getItem('quiz222-r3state');
		 if (r3state != null) {
			 _r3state = new Set(JSON.parse(r3state));
		 } else {
			 _r3state = new Set();
		 }
	 };
	 
	 _currentState.saveToLocalStorage = function() {
		 $window.localStorage.setItem('quiz222-team-scores', JSON.stringify(_teamScores));
		 $window.localStorage.setItem('quiz222-questions-closed', JSON.stringify(_questionClosed));
		 $window.localStorage.setItem('quiz222-r1state', JSON.stringify(_r1state));
		 $window.localStorage.setItem('quiz222-r2state', JSON.stringify(
				 {stack: _r2state.stack, usedTopics: Array.from(_r2state.usedTopics) }));
		 $window.localStorage.setItem('quiz222-r3state', JSON.stringify(Array.from(_r3state)));
	 };
	 
	 _currentState.loadFromLocalStorage();
	 return _currentState;
  });