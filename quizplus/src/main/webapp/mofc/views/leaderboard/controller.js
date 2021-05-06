quizRunnerModule
  .controller('LeaderBoardPageController', function ($scope, $routeParams, $location, Storage, $http, $mdDialog, QuestionData) {
    $http({
      method : 'GET',
      url : '/api/hph/getscores'
    }).then(function(response) {
      $scope.scores = response.data;
    }, function(response) {
      console.log(response);
    });
   
    $scope.goTo = function(path) {
      $location.path(path);
    };
  });