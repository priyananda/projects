quizRunnerModule
  .controller('LandingPageController', function ($scope, $http, $mdDialog, $location, Storage) {
    $scope.person = Storage.get();
    $scope.registerUser = function() {
      if(this.nameInput === undefined || this.nameInput == null || this.nameInput.length < 1)
        return;
      $http({
        method : 'GET',
        url : '/api/olq/register',
        params: {'n': this.nameInput}
      }).then(function(response) {
        $scope.person = response.data;
        Storage.save($scope.person);
      }, function(response) {
        console.log(response);
      });
    };
   
    $scope.startQuiz = function(evt){
      $location.path('/q/1');
    };
  });