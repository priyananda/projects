angular.module('QuizRunnerModule')
  .controller('QuestionController', function ($scope, $routeParams, $location) {
	var qid = $routeParams.id;
	$scope.goto = function(where){
		$location.path(where);
	};
  });
