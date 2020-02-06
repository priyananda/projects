quizRunnerModule
  .controller('CrystalController', function ($scope, $location, QuizState, $http) {
	  $scope.goto = function(where){
			$location.path(where);
		};
		$scope.loadData = function() {
		  $http({method: 'GET', url: '/cr/action/get'}).then(
		      function (response) {
		        $scope.result = response.data;
		      }, function (response) {
            console.log(response);
          });
		};
		$scope.loadData();
  });