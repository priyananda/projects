quizRunnerModule.controller('MatchController', function($scope, $routeParams,
    $location, $http) {
  $scope.score = 0;
  $scope.data = JSON.parse(JSON.stringify($scope.ctrl.matchdata));
  $scope.allCorrect = false;
  
  $scope.evaluateState = function() {
    $scope.score = 0;
    for (row of $scope.data.rows) {
      for (cell of row) {
        if (cell.selected === cell.answer) {
          $scope.score += 1;
        }
      }
    }
    $scope.allCorrect = ($scope.score === 9);
  };
});

quizRunnerModule.component('match', {
  templateUrl : 'components/match/page.ng.html',
  controller : 'MatchController',
  controllerAs : 'ctrl',
  bindings : {
    matchdata : '=',
  },
});