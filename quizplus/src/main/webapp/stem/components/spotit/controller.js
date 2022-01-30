quizRunnerModule.controller('SpotItController', function($scope, $routeParams,
    $location, $http) {
  $scope.score = 0;
  $scope.characters = [
    {name: 'Zoidberg', ansCol: 'D', ansRow: '2'},
    {name: 'Stitch', ansCol: 'C', ansRow: '3'},
    {name: 'Marvin', ansCol: 'A', ansRow: '1'},
    {name: 'Optimus Prime', ansCol: 'C', ansRow: '1'},
    {name: 'Yoda', ansCol: 'A', ansRow: '2'},
  ];
  $scope.allCorrect = false;
  
  $scope.evaluateState = function() {
    $scope.score = 0;
    for (c of $scope.characters) {
      if(c.selRow === c.ansRow && c.selCol === c.ansCol) {
        $scope.score += 1;
      }
    }
    $scope.allCorrect = ($scope.score === 5);
  };
});

quizRunnerModule.component('spotit', {
  templateUrl : 'components/spotit/page.ng.html',
  controller : 'SpotItController',
  controllerAs : 'ctrl',
});