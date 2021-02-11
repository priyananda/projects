quizRunnerModule
  .controller('LandingPageController', function ($scope, $http, $location, $window, Storage, QuestionData, $mdDialog) {
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
        $window.location.reload();
      }, function(response) {
        console.log(response);
      });
    };
    
    $scope.goto = function (key) {
      var utcDate = new Date();
      var pstDate = new Date(utcDate.toLocaleString('en-US', { timeZone: 'America/Los_Angeles' }));
      if (pstDate.getHours() < 18) {
        $mdDialog.show(
          $mdDialog.alert()
            .clickOutsideToClose(true)
            .title('Not Yet Time') 
            .textContent('The Quiz will open at 6 PM Pacific.')
            .ok('OK!')
          );
      } else {
        $location.path('/q/' + key);
      }
    };
  });