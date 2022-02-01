quizRunnerModule.controller('WordleController', function($scope,
    $routeParams, $location, $http) {

  $scope.correct = false;
  const ANSWER = "19254";
  const POSITIONS = [-1,0,2,-1,4,3,-1,-1,-1,1];
  $scope.attempts = [];

  function showError() {
    $scope.errorMessage = "Invalid guess, must be 5 digits and no repeats";
  }

  function hasRepeats(s) {
    var parts = s.split("");
    var map = new Map();
    for (i = 0; i < parts.length; ++i) {
      if (map.get(parts[i]))
        return true;
      map.set(parts[i], 1);
    }
    return false;
  }

  $scope.evaluate = function() {
	$scope.errorMessage = null; 
	if ($scope.inputNumber === undefined || $scope.inputNumber === null ||
		$scope.inputNumber.length !== 5 || hasRepeats($scope.inputNumber)) {
      showError();
      return;
	}

    var inpDigits = $scope.inputNumber.split("");
    var attempt = { digits: []};
	for (i = 0; i < 5; ++i) {
      var digit = {value: inpDigits[i]};
      var pos = POSITIONS[parseInt(inpDigits[i])];
      if (pos === i) {
        digit.cls = "wordle-green";
      } else if (pos === -1) {
        digit.cls = "wordle-grey";
      } else {
        digit.cls = "wordle-yellow";
      }
	  attempt.digits.push(digit);
    }
	$scope.attempts.push(attempt);
    if (ANSWER === $scope.inputNumber) {
      $scope.correct = true;
    }
    $scope.inputNumber = "";
  };
 
});

quizRunnerModule.component('wordle', {
  templateUrl : 'components/wordle/page.ng.html',
  controller : 'WordleController',
  controllerAs : 'ctrl'
});