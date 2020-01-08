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
	this.teamMenu = [{
		text: '+10',
	    click: function ($itemScope, $event, modelValue, text, $li) {
	      $scope.addToTeam($itemScope.item, 10);
	    }
      },{
	    text: '+5',
	    click: function ($itemScope, $event, modelValue, text, $li) {
	      $scope.addToTeam($itemScope.item, 5);
	    }
    }];
});

quizRunnerModule.component('scoreboard', {
  templateUrl: 'scripts/scoreboard.ng.html',
  bindings: {
    scores: '='
  },
  controller: 'ScoreBoardController',
  controllerAs: 'ctrl'
});