quizRunnerModule
  .controller('RootController', function ($scope, $mdSidenav, QuizState) {
	  $scope.scores = QuizState.getTeamScores();
  })
  .config(function($routeProvider) {
    $routeProvider
      .when('/', {
          templateUrl : 'runner/questionchooser.ng.html',
          controller  : 'QuestionChooserController'
      })
      .when('/question/:id', {
          templateUrl : 'runner/question.ng.html',
          controller  : 'QuestionController'
      });
  })
  .config(function($mdThemingProvider) {
     $mdThemingProvider.theme('default')
     	.primaryPalette('light-blue')
     	.accentPalette('orange');
  });