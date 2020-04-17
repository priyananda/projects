quizRunnerModule
  .controller('QuestionPageController', function ($scope, $routeParams, $location, $mdSidenav, Storage, $http) {
    $scope.person = Storage.get();
    $scope.question = $routeParams.id;
    $scope.currentImage = Storage.getImage($scope.question);
    $scope.groups = [];
    $scope.video = Storage.getVideoInfo($scope.question);
    var qid = 1;
    for (g = 0; g < 6; ++g) {
      var group = {
          name: qid + '-' + (qid + 9),
          items: []
      };
      for (i = 0; i < 10; ++i) {
        group.items.push({qid: qid});
        ++qid;
      }
      $scope.groups.push(group);
    }
    
    var sendLocation = function() {
      $http({
        method : 'GET',
        url : '/api/olq/setlocation',
        params: {'p': $scope.person.pid, 'q' : $scope.question }
      }).then(function(response) {
        console.log(response);
      }, function(response) {
        console.log(response);
      });
    };
    
    $scope.goToQuestion = function(newqid) {
      $location.path('/q/' + newqid);
    };
    
    $scope.showAnswerPane = function() {
      $mdSidenav('right').open();
    };
    
    $scope.goToPrevious = function() {
      if ($scope.question > 1) {
        $scope.goToQuestion($scope.question - 1);
      }
    };
    
    $scope.goToNext = function() {
      if ($scope.question < 60) {
        $scope.goToQuestion(++$scope.question);
      }
    };
    
    $scope.shouldShowChatButton = function() {
      return !$mdSidenav('left').isOpen() && !$mdSidenav('left').isLockedOpen();
    };
    
    $scope.openChatWindow = function() {
      $mdSidenav('left').open();
    };
  });