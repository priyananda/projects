quizRunnerModule.controller('SolventController', function($scope,
    $routeParams, $location, $http) {

  const OPTIONS = ["1", "2", "3", "4", "5", "6", "7", "8", "9"];
  $scope.cells = [];
  for (i = 0; i < 2; ++i) {
   var cell = {};
   cell.options = OPTIONS;
   $scope.cells.push(cell);
  }
  $scope.correct = false;

  $scope.evaluateState = function() {
	$scope.correct = false;
    for (i = 0; i < 2; ++i) {
	  if ($scope.cells[i].value === undefined || $scope.cells[0].value === '' || $scope.cells[0].value === null)
	    return;
    }
    var val1 = parseInt($scope.cells[0].value);  
    var val2 = parseInt($scope.cells[1].value);
	$scope.acidIcons = '';
	$scope.baseIcons = '';
	for (i = 0; i < val1; ++i) {
    	$scope.acidIcons += '\u{1F9EA}';
	}
	for (i = 0; i < val2; ++i) {
    	$scope.baseIcons += '\u2697';
	}
	if (val1 == 3 && val2 == 7) {
		$scope.resultIcon = '\u{1F9EB}';
		$scope.correct = true;
	}else{
        $scope.resultIcon = '\u{1F4A5}';
    }
  };
 
});

quizRunnerModule.component('solvent', {
  templateUrl : 'components/solvent/page.ng.html',
  controller : 'SolventController',
  controllerAs : 'ctrl'
});