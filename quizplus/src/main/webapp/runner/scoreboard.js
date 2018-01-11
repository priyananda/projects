let quizRunner = angular.module('QuizRunnerModule'); 

quizRunner.controller('ScoreBoardController', function ($scope) {
	ctrl = this;
});

quizRunner.component('scoreboard', {
  templateUrl: 'runner/scoreboard.ng.html',
  bindings: {
    scores: '='
  },
  controller: 'ScoreBoardController',
  controllerAs: 'ctrl'
});