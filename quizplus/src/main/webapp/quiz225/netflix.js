quizRunnerModule
  .controller('NetflixPageController', function ($scope, $routeParams, $location, QuizState) {
	  if (QuizState.getGraph() === null) {
		  QuizState.setGraph(new Graph());
	  }
  });