quizRunnerModule.controller('RootController',
    function($scope, $mdSidenav, $location, Storage) {
      $scope.person = Storage.getPerson();
  
      $scope.getScore = function() {
        return Storage.getScore().size;
      };
      $scope.goTo = function(where) {
        $location.path(where);
      };
      $scope.showCredits = function() {
        
      };
      $scope.showHelp = function() {
        
      };
      $scope.logOut = function() {
        
      };
    }).config(function($routeProvider) {
  $routeProvider.when('/', {
    templateUrl : 'views/landing/page.ng.html',
    controller : 'LandingPageController'
  }).when('/q/:key/:arena', {
    templateUrl : 'views/question/page.ng.html',
    controller : 'QuestionPageController'
  }).when('/s/:setid', {
    templateUrl : 'views/arena/page.ng.html',
    controller : 'ArenaPageController'
  }).when('/lb', {
    templateUrl : 'views/leaderboard/page.ng.html',
    controller : 'LeaderBoardPageController'
  });
}).config(function($mdThemingProvider) {
  $mdThemingProvider.theme('default').primaryPalette('blue', {
    'default' : '900'
  }).accentPalette('grey');
});
