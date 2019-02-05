quizRunnerModule
  .controller('ScoreBoardController', function ($scope, QuizState) {
	ctrl = this;
	$scope.addToTeam = function(teamscore, delta) {
		teamscore.points += delta;
		QuizState.saveToLocalStorage();
	};
	$scope.clearStorage = function() {
		QuizState.clearLocalStorage();
	};
	$scope.plus100 = function() {
		QuizState.addToAllTeams(100);
		QuizState.saveToLocalStorage();
	};
	$scope.minus100 = function() {
		QuizState.addToAllTeams(-100);
		QuizState.saveToLocalStorage();
	};
});

quizRunnerModule.component('scoreboard', {
  templateUrl: 'runner/scoreboard.ng.html',
  bindings: {
    scores: '='
  },
  controller: 'ScoreBoardController',
  controllerAs: 'ctrl'
});