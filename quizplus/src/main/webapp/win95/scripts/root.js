quizRunnerModule
  .controller('RootController', function ($scope, $mdSidenav, QuizState, AuthState, $location) {
	  $scope.scores = QuizState.getTeamScores();
  })
  .config(function($routeProvider) {
    $routeProvider
      .when('/', {
          templateUrl : 'scripts/landingpage.ng.html',
          controller  : 'LandingPageController'
      })
      .when('/question/:id', {
          templateUrl : 'scripts/question.ng.html',
          controller  : 'QuestionController'
      });
  })
  .config(function($mdThemingProvider) {
     $mdThemingProvider.theme('default')
     	.primaryPalette('blue', {
     		'default' : '900'
     	})
     	.accentPalette('grey');
  });