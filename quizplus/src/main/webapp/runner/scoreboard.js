quizRunnerModule
  .controller('ScoreBoardController', function ($scope, QuizState) {
	ctrl = this;
	$scope.plusFive = function(teamscore) {
		teamscore.points += 5;
		QuizState.saveToLocalStorage();
	};
	$scope.minusFive = function(teamscore) {
		teamscore.points -= 5;
		QuizState.saveToLocalStorage();
	};
	$scope.clearStorage = function() {
		QuizState.clearLocalStorage();
	}
});

quizRunnerModule.component('scoreboard', {
  templateUrl: 'runner/scoreboard.ng.html',
  bindings: {
    scores: '='
  },
  controller: 'ScoreBoardController',
  controllerAs: 'ctrl'
});