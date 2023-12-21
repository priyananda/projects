quizRunnerModule.controller('CricketController', function($scope, $routeParams,
    $location, $http) {
  $scope.stages = [
    {image: "img/cr-book-closed.jpg", runs: 0},
    {image: "img/cr-book-1.jpg", runs: 6},
    {image: "img/cr-book-2.jpg", runs: 2},
    {image: "img/cr-book-3.jpg", runs: 4},
    {image: "img/cr-book-4.jpg", runs: 2},
    {image: "img/cr-book-5.jpg", runs: 0},
  ];
  $scope.runs = [];
  $scope.totalScore = 0;
  $scope.selectedIndex = 0;
  $scope.selectedImage = $scope.stages[$scope.selectedIndex].image;
 
  $scope.playTurn = function() {
    if ($scope.selectedIndex < $scope.stages.length - 1) {
      ++$scope.selectedIndex;
    }
    $scope.selectedImage = $scope.stages[$scope.selectedIndex].image;
    $scope.runs.push($scope.stages[$scope.selectedIndex]);
    $scope.totalScore = $scope.totalScore + parseInt($scope.stages[$scope.selectedIndex].runs);
  };
  
  $scope.donePlay = function() {
    return $scope.selectedIndex >= $scope.stages.length - 1;
  };
});

quizRunnerModule.component('cricket', {
  templateUrl : 'components/cricket/page.ng.html',
  controller : 'CricketController',
  controllerAs : 'ctrl'
});