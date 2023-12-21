quizRunnerModule
  .controller('QuestionPageController', function ($scope, $routeParams, $location, Storage, $http, $mdDialog, QuestionData) {
    $scope.person = Storage.getPerson();
    $scope.key = $routeParams.key;
    $scope.answerText = "";
    $scope.content = QuestionData.getContent($scope.key);
    $scope.score = Storage.getScore();
    $scope.showHint = false;
    
    $scope.attemptAnswer = function() {
      var confirm = $mdDialog.prompt()
      .title('Enter the answer to this puzzle')
      .textContent('The answer is a phrase without spaces or punctuation.')
      .placeholder('Enter your answer here')
      .ok('Try')
      .cancel('Cancel');

      $mdDialog.show(confirm).then(function(result) {
        $scope.postAnswer(result);
      }, function(){});
    };
    
    $scope.go = function(path) {
      $location.path(path);
    };
    
    $scope.postAnswer = function(answerText) {
      $http({
        method : 'GET',
        url : '/api/rr/postanswer',
        params: {'k': $scope.key, 'p' : $scope.person.pid, 'a' : answerText}
      }).then(function(response) {
        var isSuccess = (response.data.status == "Success");
        var alert = $mdDialog.alert()
          .title('Answer')
          .textContent(isSuccess ? 'Congratulations! Correct Answer.' : 'Oh No! Incorrect Answer')
          .ok('OK');
        $mdDialog.show(alert).then(function() {
          if (isSuccess) {
            $scope.score.set($scope.key, 1);
            Storage.saveScore($scope.score);
          }
        }, function(){});
      }, function(response) {
        console.log(response);
      });
    };
    
    $scope.doShowHint = function(){
        $scope.showHint = true;
    };
  });