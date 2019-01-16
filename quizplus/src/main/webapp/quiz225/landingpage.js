quizRunnerModule.controller('LandingPageController', function($scope,
		$routeParams, $location, QuizState) {
	ctrl = this;
	$scope.searchText = "";
	$scope.selectedItem = "";
	$scope.options = [ "Pete's quiz", "Is Pete the Pete in For Pete's Sake?",
			"Will Pete win the Nobel Prize?",
			"What does the fox say? asks Pete", "Royal Wedding",
			"Royale with Cheese" ];
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
		}
	};
	function createFilterFor(query) {
		var lowercaseQuery = query.toLowerCase();
		return function filterFn(state) {
			return (state.toLowerCase().indexOf(lowercaseQuery) >= 0);
		};
	}
});