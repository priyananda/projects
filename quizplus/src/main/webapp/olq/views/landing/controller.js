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
      var currentTimePdt = new Date(new Date().toLocaleString("en-US", {timeZone: "America/Los_Angeles"}));
      if (currentTimePdt.getHours() < 18) {
        $mdDialog.show(
            $mdDialog.alert()
              .parent(angular.element(document.querySelector('#popupContainer')))
              .clickOutsideToClose(true)
              .title('Quiz hasn\'t started yet')
              .textContent('Quiz will unlock at 18:00, currently it is ' + currentTimePdt.toLocaleString('en-US'))
              .ok('OK!')
              .targetEvent(evt)
          );
      } else {
        $location.path('/q/1');
      }
    };
  });