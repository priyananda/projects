quizRunnerModule
  .controller('ScoreBoardController', function ($scope) {
	ctrl = this;
	$scope.plusFive = function(teamscore) {
		teamscore.points += 5;
	};
	$scope.minusFive = function(teamscore) {
		teamscore.points -= 5;
		if (teamscore.points < 0)
			teamscore.points = 0;
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