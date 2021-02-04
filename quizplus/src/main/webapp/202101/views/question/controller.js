quizRunnerModule
  .controller('QuestionPageController', function ($scope, $routeParams, $location, Storage, $http, $mdDialog, QuestionData) {
    $scope.person = Storage.getPerson();
    $scope.set = $routeParams.set;
    $scope.id = $routeParams.id;
    $scope.answerText = "";
    $scope.content = QuestionData.getContent($scope.set, $scope.id);
    $scope.showHint = false;
    
    $scope.icons = [];
    for (i = 1; i < 14; ++i) {
      $scope.icons.push({
        url: "/202101/img/cards/" + $scope.set + "_" + i + ".png",
        link: "/q/" + $scope.set + "/" + i,
        isSelected: (i == $scope.id)
      });
    }
    
    $scope.attemptAnswer = function(ev) {
      $mdDialog.show({
        controller: DialogController,
        controllerAs: 'ctrl',
        templateUrl: 'views/question/attempt.ng.html',
        parent: angular.element(document.body),
        targetEvent: ev,
        clickOutsideToClose: true,
      });
    };
    
    $scope.go = function(path) {
      $location.path(path);
    };
    
    function DialogController($mdDialog) {
      ctrl = this;
      var args = {
        t: $scope.person.team,
        s: $scope.set,
        q: $scope.id,
      };
      $http({
        method : 'GET',
        url : '/api/jan21/getanswers',
        params: args,
      }).then(function(response) {
        ctrl.attempts = response.data;
      }, function(response) {
        console.log(response);
      });
      
      ctrl.hide = function() {
        $mdDialog.hide();
      };
      
      ctrl.postAnswer = function() {
        var args = {
          t: $scope.person.team,
          n: $scope.person.name,
          a: ctrl.answerText,
          s: $scope.set,
          q: $scope.id,
        };
        $http({
          method : 'GET',
          url : '/api/jan21/postanswer',
          params: args
        }).then(function(response) {
          ctrl.attempts = response.data;
        });
      };
    }
  });