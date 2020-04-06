quizRunnerModule
  .controller('QuestionPageController', function ($scope, $routeParams, $location, $http, $mdSidenav, Storage) {
    $scope.person = Storage.get();
    $scope.currentImage = "../test/Slide1.jpg"
    
    $scope.showAnswerPane = function() {
      $mdSidenav('right').open();
    };
  });