quizRunnerModule.controller('SpotItController', function($scope, $routeParams,
    $location, $http) {
  $scope.score = 0;
  $scope.characters = [
    {name: 'Mulan', ansCol: 'A', ansRow: '3'},
    {name: 'Lady & Tramp', ansCol: 'D', ansRow: '5'},
    {name: 'Tigger', ansCol: 'C', ansRow: '2'},
    {name: 'Peter Pan', ansCol: 'C', ansRow: '1'},
    {name: 'Hercules', ansCol: 'B', ansRow: '2'},
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