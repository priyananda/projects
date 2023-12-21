quizRunnerModule
  .controller('ScoreBoardController', function ($scope, $mdMenu, QuizState) {
	ctrl = this;
	$scope.addToTeam = function(teamscore, delta) {
		teamscore.points += delta;
		QuizState.saveToLocalStorage();
	};
	$scope.clearStorage = function() {
		QuizState.clearLocalStorage();
	};
	$scope.showSnapMenu = function(event) {
		$mdMenu.open(event);
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