quizRunnerModule
  .controller('InstagramPageController', function ($scope, $routeParams, $location, QuizState) {
	  $scope.questions = [];
	  for (i = 13; i <= 24; ++i) {
		  var closed = QuizState.isQuestionClosed(i)
		  $scope.questions.push({
			id: i,
		  	image: "/quiz225/img/ig" + (closed ? "" : i) + ".png"
		  });
	  }
  });