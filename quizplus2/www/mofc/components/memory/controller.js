quizRunnerModule.controller('MemoryController', function($scope, $routeParams,
    $location, $http, $timeout) {
  $scope.data = JSON.parse(JSON.stringify($scope.ctrl.memorydata));
  $scope.allCorrect = false;
  
  $scope.flip = function(cell) {
    if (!cell.done && !cell.visible) {
      cell.visible = true;
    }
    $scope.evaluateState();
  }
  
  $scope.evaluateState = function() {
    var doneCells = 0;
    var visibleCells = [];
    for (row of $scope.data.rows) {
      for (cell of row) {
        if (cell.done) {
          doneCells += 1;
        } else if (cell.visible) {
          visibleCells.push(cell);
        }
      }
    }
    if (visibleCells.length === 2) {
      if (visibleCells[0].k === visibleCells[1].k) {
        doneCells += 2;
        visibleCells[0].done = true;
        visibleCells[1].done = true;
      } else {
        $timeout(function(){
          visibleCells[0].visible = false;
          visibleCells[1].visible = false;
        }, 2000);
      }
    } else if (visibleCells.length > 2) {
      visibleCells.forEach(function(cell){
        cell.visible = false;
      });
    }
    $scope.allCorrect = (doneCells === 12);
  };
});

quizRunnerModule.component('memory', {
  templateUrl : 'components/memory/page.ng.html',
  controller : 'MemoryController',
  controllerAs : 'ctrl',
  bindings : {
    memorydata : '=',
  },
});