quizRunnerModule.controller('RootController',
    function($scope, $mdSidenav, $location, Storage) {
      $scope.person = Storage.getPerson();
    }).config(function($routeProvider) {
  $routeProvider.when('/', {
    templateUrl : 'views/landing/page.ng.html',
    controller : 'LandingPageController'
  }).when('/q/:set/:id', {
    templateUrl : 'views/question/page.ng.html',
    controller : 'QuestionPageController'
  });
}).config(function($mdThemingProvider) {
  $mdThemingProvider.theme('default').primaryPalette('blue', {
    'default' : '900'
  }).accentPalette('grey');
});
