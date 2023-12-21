quizRunnerModule
  .controller('HiddenPageController', function ($scope, $location, $mdSidenav, Storage, $http) {
    $scope.person = Storage.get();
    $scope.question = 30;
    $scope.currentImage = Storage.getImage($scope.question);
    
    $scope.goToQuestion = function(newqid) {
      $location.path('/q/' + newqid);
    };
    
    $scope.showAnswerPane = function() {
      $mdSidenav('right').open();
    };
    
    $scope.returnToQuiz = function() {
      $location.path('/q/30');
    };
    
    $scope.shouldShowChatButton = function() {
      return !$mdSidenav('left').isOpen() && !$mdSidenav('left').isLockedOpen();
    };
    
    $scope.openChatWindow = function() {
      $mdSidenav('left').open();
    };
  });