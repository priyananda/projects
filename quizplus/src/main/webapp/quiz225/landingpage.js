quizRunnerModule.controller('LandingPageController', function($scope,
		$routeParams, $location, QuizState) {
	ctrl = this;
	$scope.searchText = "";
	$scope.selectedItem = "";
	$scope.options = [
		"Pete wrecks the Internet", //0
		"Is Pete the Pete in For Pete's Sake?", //1
		"Will Pete win the Nobel Prize?", //2
		"Pete na mila re man ka", //3
		"India vs Australia", //4
		"Royale with Cheese", //5
		"Indian restaurants in Antarctica", //6
		"Happy Birthday!"]; //7
	$scope.querySearch = function(searchStr) {
		var results = searchStr ? $scope.options.filter(createFilterFor(searchStr))
				: $scope.options;
		return results;
	};
	$scope.goto = function(where){
		$location.path(where);
		$scope.$apply();
	};
	$scope.onSearch = function() {
		if ($scope.selectedItem == $scope.options[0]) {
			$scope.goto("/rounds");
		} else if ($scope.selectedItem == $scope.options[4]) {
			$scope.goto("/congrats");
		} else if ($scope.selectedItem == $scope.options[7]) {
			$scope.goto("/nb");
		}
	};
	function createFilterFor(query) {
		var lowercaseQuery = query.toLowerCase();
		return function filterFn(state) {
			return (state.toLowerCase().indexOf(lowercaseQuery) >= 0);
		};
	}
});