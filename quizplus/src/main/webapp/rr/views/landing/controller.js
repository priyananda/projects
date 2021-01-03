quizRunnerModule
  .controller('LandingPageController', function ($scope, $http, $location, Storage, QuestionData) {
    $scope.person = Storage.getPerson();
    $scope.score = Storage.getScore();
    $scope.join = function(key) {
      if(this.nameInput === undefined || this.nameInput == null || this.nameInput.length < 1)
        return;
      $http({
        method : 'GET',
        url : '/api/rr/register',
        params: {'n': this.nameInput}
      }).then(function(response) {
        $scope.person = response.data;
        Storage.savePerson($scope.person);
      }, function(response) {
        console.log(response);
      });
    };
    
    $scope.goto = function (key) {
      $location.path('/q/' + key);
    };
    
    $scope.isAnswered = function(key) {
      return ($scope.score.get(key) !== undefined);
    };
    
    $scope.sets = [
      QuestionData.getAllQuestions(0),
      QuestionData.getAllQuestions(1),
      QuestionData.getAllQuestions(2)];
  });