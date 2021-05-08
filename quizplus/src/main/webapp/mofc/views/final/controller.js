quizRunnerModule
  .controller('FinalPageController', function ($scope, $routeParams, $location, Storage, $http, $mdDialog, QuestionData) {
    $scope.suspects = QuestionData.getSuspects();
    
    $scope.goTo = function(path) {
      $location.path(path);
    };
    
    $scope.isAnswered = function(key) {
      return (Storage.getScore().get(key) !== undefined);
    };
  });