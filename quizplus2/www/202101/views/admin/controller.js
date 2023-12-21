quizRunnerModule
  .controller('AdminPageController', function ($scope, $routeParams, $location, $http) {
    $scope.persons = [];
    for (i = 0; i < 6; ++i) {
      $scope.persons.push({
        name: "Quiz Master",
        team: i + 1,
      });
    }
  });