quizRunnerModule
  .controller('EbayPageController', function ($scope, $routeParams, $location, QuizState) {
	  $scope.goto = function(where){
			$location.path(where);
	  };
  });