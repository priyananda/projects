quizRunnerModule.controller('CricketController', function($scope, $routeParams,
    $location, $http) {
  $scope.cells = [];
  for (var i = 0; i < 12; ++i) {
    $scope.cells.push({value: "0"});
  }
  
  function recalcTable() {
    var bat1 = {r: 0, b: 0, f: 0};
    var bat2 = {r: 0, b: 0, f: 0};
    var bowl1 = 0;
    var bowl2 = 0;
    var currBat1 = true;
    for (var b = 0; b < 12; ++b) {
      var currCell = parseInt($scope.cells[b].value);
      if (currCell === 6) return false;
      if (b < 6)
        bowl1 += currCell;
      else
        bowl2 += currCell;
      if (currBat1) {
        bat1.r += currCell;
        bat1.b++;
        bat1.f += (currCell === 4 ? 1 : 0);
      } else {
        bat2.r += currCell;
        bat2.b++;
        bat2.f += (currCell === 4 ? 1 : 0);
      }
      if (currCell === 1)
        currBat1 = !currBat1;
      if (b == 5)
        currBat1 = !currBat1;
    }
    return (bat1.r === 6) && (bat1.b === 4) && (bat1.f === 1) &&
      (bat2.r === 11) && (bat2.b === 8) && (bat2.f === 1) &&
      (bowl1 === 8) && (bowl2 === 9);
  }
  
  $scope.changeValue = function(cell){
    switch (cell.value) {
      case "0": cell.value = "1"; break;
      case "1": cell.value = "2"; break;
      case "2": cell.value = "4"; break;
      case "4": cell.value = "6"; break;
      case "6": cell.value = "0"; break;
    }
    $scope.allCorrect = recalcTable();
  };
});

quizRunnerModule.component('cricket', {
  templateUrl : 'components/cricket/page.ng.html',
  controller : 'CricketController',
  controllerAs : 'ctrl'
});