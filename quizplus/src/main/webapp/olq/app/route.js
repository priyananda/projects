quizRunnerModule.controller('RootController',
    function($scope, $mdSidenav, $location) {
    }).config(function($routeProvider) {
  $routeProvider.when('/', {
    templateUrl : 'views/landing/page.ng.html',
    controller : 'LandingPageController'
  }).when('/q/:id', {
    templateUrl : 'views/question/page.ng.html',
    controller : 'QuestionPageController'
  }).when('/hidden', {
    templateUrl : 'views/hidden/page.ng.html',
    controller : 'HiddenPageController'
  });
}).config(function($mdThemingProvider) {
  $mdThemingProvider.theme('default').primaryPalette('blue', {
    'default' : '900'
  }).accentPalette('grey');
});
