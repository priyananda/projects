quizRunnerModule
  .controller('ArenaPageController', function ($scope, $routeParams, $location, ScoreManager, $http, $mdDialog, QuestionData) {
    $scope.setId = $routeParams.setid;
    $scope.arenaData = QuestionData.getArena($scope.setId);
    $scope.bgStyle = {
      'background-image': 'url(' + $scope.arenaData.bgImg + ')',
      'background-repeat': 'no-repeat',
      'background-size': 'cover'
    };
    
    $scope.goTo = function(path) {
      $location.path(path);
    };
    
    $scope.isAnswered = function(key) {
      return ScoreManager.isSolved(key);
    };
  });