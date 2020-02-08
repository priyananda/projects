quizRunnerModule
  .controller('CrUiStatusController', function ($scope, $routeParams, $location, $http) {
    $scope.team = $routeParams.team;
    $scope.goto = function(where){
      $location.path(where);
    };
    $scope.loadData = function() {
      $http({method: 'GET', url: '/cr/action/get'}).then(
          function (response) {
            $scope.teamStatus = response.data[$scope.team - 1];
          }, function (response) {
            console.log(response);
          });
    };
    $scope.loadData();
  });

const QCAT_MAP = [
  'PHYSICAL',
  'MENTAL',
  'MYSTERY',
  'SKILL'
];

quizRunnerModule
.controller('CrUiAttemptController', function ($scope, $routeParams, $location, $http) {
  $scope.team = $routeParams.team;
  $scope.qcat = $routeParams.qcat;
  $scope.goto = function(where){
    $location.path(where);
  };
  $scope.checkAnswer = function() {
    var args = {
      team: $scope.team,
      q: QCAT_MAP[$scope.qcat],
      a: $scope.answer
    };
    $http({method: 'GET', url: '/cr/action/check', params: args}).then(
        function (response) {
          $scope.response = response.data;
        }, function (response) {
          console.log(response);
        });
  };
});

quizRunnerModule.controller('RootController',
    function($scope, $mdSidenav, QuizState, $location) {
      $scope.scores = QuizState.getTeamScores();
    }).config(function($routeProvider) {
        $routeProvider.when('/', {
          templateUrl : 'templates/landingpage.ng.html',
          controller : 'EmptyController'
        }).when('/status/:team', {
          templateUrl : 'templates/crui.status.ng.html',
          controller : 'CrUiStatusController'
        }).when('/attempt/:team/:qcat', {
          templateUrl : 'templates/crui.attempt.ng.html',
          controller : 'CrUiAttemptController'
        });
    }).config(function($mdThemingProvider) {
        $mdThemingProvider.theme('default').primaryPalette('blue', {
           'default' : '900'
        }).accentPalette('grey');
    });