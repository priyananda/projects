quizRunnerModule
  .controller('QuestionPageController', function ($scope, $routeParams, $location, Storage, $http, $mdDialog, QuestionData) {
    $scope.person = Storage.getPerson();
    $scope.key = $routeParams.key;
    $scope.arenaData = QuestionData.getArena($routeParams.arena);
    $scope.content = QuestionData.getContent($scope.key);
    $scope.score = Storage.getScore();
    
    $scope.attemptAnswer = function() {
      $mdDialog.show({
        controller: AttemptDialogController,
        controllerAs: 'ctrl',
        templateUrl: 'views/question/attempt.ng.html',
        parent: angular.element(document.body),
        clickOutsideToClose: true,
      });
    };
    
    $scope.go = function(path) {
      $location.path(path);
    };
    
    function AttemptDialogController($mdDialog) {
      ctrl = this;
      ctrl.person = $scope.person;
      ctrl.questionKey = $scope.key;
      ctrl.suspect = $scope.arenaData.suspect;
    }
  });