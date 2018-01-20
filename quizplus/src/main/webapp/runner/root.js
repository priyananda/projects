quizRunnerModule
  .controller('RootController', function ($scope, $mdSidenav, QuizState, AuthState, $location) {
	  $scope.scores = QuizState.getTeamScores();
	  if (!AuthState.isLoggedIn()) {
		  $location.path('/error');
	  }
  })
  .config(function($routeProvider) {
    $routeProvider
      .when('/', {
          templateUrl : 'quiz219/questionchooser.ng.html',
          controller  : 'QuestionChooserController'
      })
      .when('/question/:id', {
          templateUrl : 'runner/question.ng.html',
          controller  : 'QuestionController'
      })
      .when('/error', {
    	  templateUrl : 'runner/errorpage.ng.html',
          controller  : 'ErrorPageController'
      });
  })
  .config(function($mdThemingProvider) {
     $mdThemingProvider.theme('default')
     	.primaryPalette('light-blue')
     	.accentPalette('orange');
  });