quizRunnerModule
  .controller('RootController', function ($scope, $mdSidenav, QuizState, AuthState, $location) {
	  $scope.scores = QuizState.getTeamScores();
  })
  .config(function($routeProvider) {
    $routeProvider
      .when('/', {
          templateUrl : 'quiz225/landingpage.ng.html',
          controller  : 'LandingPageController'
      })
      .when('/rounds', {
          templateUrl : 'quiz225/rounds.ng.html',
          controller  : 'RoundsPageController'
      })
      .when('/congrats', {
          templateUrl : 'quiz225/congrats.ng.html',
          controller  : 'EmptyController'
      })
      .when('/wiki', {
          templateUrl : 'quiz225/wiki.ng.html',
          controller  : 'WikiPageController'
      })
      .when('/yt', {
          templateUrl : 'quiz225/yt.ng.html',
          controller  : 'EmptyController'
      })
      .when('/ebay', {
          templateUrl : 'quiz225/ebay.ng.html',
          controller  : 'EbayPageController'
      })
      .when('/ig', {
          templateUrl : 'quiz225/ig.ng.html',
          controller  : 'InstagramPageController'
      })
      .when('/netflix', {
          templateUrl : 'quiz225/netflix.ng.html',
          controller  : 'NetflixPageController'
      })
      .when('/pornhub', {
          templateUrl : 'quiz225/pronhub.ng.html',
          controller  : 'EmptyController'
      })
      .when('/question/:id', {
          templateUrl : 'runner/question.ng.html',
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