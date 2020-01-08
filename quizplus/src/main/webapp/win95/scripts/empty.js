quizRunnerModule
  .controller('EmptyController', function ($scope, $location, QuizState) {
	  $scope.goto = function(where){
			$location.path(where);
		};
  });