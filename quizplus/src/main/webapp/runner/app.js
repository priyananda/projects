angular
  .module('QuizRunnerModule',['ngMaterial', 'ngMessages', 'material.svgAssetsCache', 'ngRoute', 'chart.js'])
  .controller('RootController', function ($scope, $mdSidenav) {
	  $scope.scores = [
		{name: "Team 1", points: 100},
		{name: "Team 2", points: 320},
		{name: "Team 3", points: 320},
		{name: "Team 4", points: 320},
		{name: "Team 5", points: 320},
		{name: "Team 6", points: 320}
	  ];
	  $scope.testVar = "Nakkan";
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