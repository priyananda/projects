quizRunnerModule.controller('MinecraftController', function($scope, $routeParams,
    $location, $http, $timeout) {
  $scope.data = [];
  for (i = 0; i < 5; ++i){
    var row = [];
    for (j = 0; j < 5; ++j)
      row.push({image: 'img/grass.png'});
    $scope.data.push(row);
  }
  $scope.allCorrect = false;
  
  $scope.flip = function(cell) {
    switch (cell.image) {
      case 'img/grass.png':
        cell.image = 'img/obsidian.png';
        break;
      case 'img/obsidian.png':
        cell.image = 'img/fire.png';
        break;
      case 'img/fire.png':
        cell.image = 'img/water.png';
        break;
      case 'img/water.png':
        cell.image = 'img/lava.png';
        break;
      case 'img/lava.png':
        cell.image = 'img/grass.png';
        break;
    }
    $scope.evaluateState();
  }
  
  $scope.evaluateState = function() {
    $scope.allCorrect = false;
    for (i = 0; i < 5; ++i) {
      if ($scope.data[0][i].image !== 'img/obsidian.png')
        return;
      if ($scope.data[4][i].image !== 'img/obsidian.png')
        return;
      if ($scope.data[i][0].image !== 'img/obsidian.png')
        return;
      if ($scope.data[i][4].image !== 'img/obsidian.png')
        return;
    }
    var counts = new Map();
    for (i = 1; i < 4; ++i) {
      for (j = 1; j< 4; ++j) {
        var cell = $scope.data[i][j].image;
        counts.set(cell, counts.has(cell) ? counts.get(cell) + 1 : 1);
      }
    }
    $scope.allCorrect = counts.get('img/fire.png') === 4 &&
      counts.get('img/water.png') === 3 &&
      counts.get('img/lava.png') === 2;
  };
});

quizRunnerModule.component('minecraft', {
  templateUrl : 'components/minecraft/page.ng.html',
  controller : 'MinecraftController',
  controllerAs : 'ctrl',
});