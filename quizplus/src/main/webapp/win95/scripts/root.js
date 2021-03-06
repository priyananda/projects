quizRunnerModule.controller('RootController',
    function($scope, $mdSidenav, QuizState, AuthState, $location) {
      $scope.scores = QuizState.getTeamScores();
    }).config(function($routeProvider) {
  $routeProvider.when('/', {
    templateUrl : 'templates/landingpage.ng.html',
    controller : 'EmptyController'
  }).when('/winamp', {
    templateUrl : 'templates/winamp.ng.html',
    controller : 'WinAmpController'
  }).when('/question/:id', {
    templateUrl : 'templates/question.ng.html',
    controller : 'QuestionController'
  }).when('/encarta', {
    templateUrl : 'templates/encarta.ng.html',
    controller : 'EncartaController'
  }).when('/yahoo', {
    templateUrl : 'templates/yahoo.ng.html',
    controller : 'YahooController'
  }).when('/crystal', {
    templateUrl : 'templates/crystal.ng.html',
    controller : 'CrystalController'
  });
}).config(function($mdThemingProvider) {
  $mdThemingProvider.theme('default').primaryPalette('blue', {
    'default' : '900'
  }).accentPalette('grey');
});