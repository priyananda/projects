quizRunnerModule
  .controller('LandingPageController', function ($scope, $http, $location, Storage, QuestionData) {
    $scope.person = Storage.getPerson();
    $scope.join = function(key) {
      if(this.nameInput === undefined || this.nameInput == null || this.nameInput.length < 1)
        return;
      $http({
        method : 'GET',
        url : '/api/jan21/register',
        params: {'n': this.nameInput}
      }).then(function(response) {
        $scope.person = response.data;
        Storage.savePerson($scope.person);
        $location.reload();
      }, function(response) {
        console.log(response);
      });
    };
    
    $scope.goto = function (key) {
      $location.path('/q/' + key);
    };
  });