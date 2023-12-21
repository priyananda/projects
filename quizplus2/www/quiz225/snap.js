quizRunnerModule
  .controller('SnapPageController', function ($scope, $routeParams, $location, QuizState) {
	  $scope.goto = function(where){
			$location.path(where);
	  };
  });