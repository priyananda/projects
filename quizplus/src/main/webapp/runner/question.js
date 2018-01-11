quizRunnerModule
  .controller('QuestionController', function ($scope, $routeParams, $location) {
	$scope.qid = $routeParams.id;
	$scope.goto = function(where){
		$location.path(where);
	};
  });
