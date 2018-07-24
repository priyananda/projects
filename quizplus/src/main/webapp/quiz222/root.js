quizRunnerModule
  .controller('RootController', function ($scope, $mdSidenav, QuizState, AuthState, $location) {
	  $scope.scores = QuizState.getTeamScores();
  })
  .config(function($routeProvider) {
    $routeProvider
      .when('/', {
          templateUrl : 'quiz222/roundchooser.ng.html',
          controller  : 'RoundChooserController'
      })
      .when('/r/:rid/q/:id', {
          templateUrl : 'runner/question.ng.html',
          controller  : 'QuestionController'
      })
      .when('/error', {
    	  templateUrl : 'runner/errorpage.ng.html',
          controller  : 'ErrorPageController'
      })
      .when('/r1', {
          templateUrl : 'quiz222/round1.ng.html',
          controller  : 'Round1Controller'
      })
      .when('/r2', {
          templateUrl : 'quiz222/round2.ng.html',
          controller  : 'Round2Controller'
      })
      .when('/r3', {
          templateUrl : 'quiz222/round3.ng.html',
          controller  : 'Round3Controller'
      })
      .when('/r4', {
          templateUrl : 'quiz222/round4.ng.html',
          controller  : 'Round4Controller'
      })
  })
  .config(function($mdThemingProvider) {
     $mdThemingProvider.theme('default')
     	.primaryPalette('orange')
     	.accentPalette('indigo');
  });