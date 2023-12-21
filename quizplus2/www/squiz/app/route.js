quizRunnerModule.controller('RootController',
    function($scope, $mdSidenav, $location, Storage) {

    }).config(function($routeProvider) {
  $routeProvider.when('/', {
    templateUrl : 'views/landing/page.ng.html',
    controller : 'LandingPageController'
  });
}).config(function($mdThemingProvider) {
  $mdThemingProvider.theme('default').primaryPalette('blue', {
    'default' : '900'
  }).accentPalette('grey');
});
