quizRunnerModule.controller('TeamNavController', function($scope, $routeParams,
    $location, $http, $interval) {
  $scope.loadData = function() {
    console.log("Loading data for team " + $scope.ctrl.person.team);
    $http({
      method : 'GET',
      url : '/api/olq/getteamdata',
      params: {'t': $scope.ctrl.person.team}
    }).then(function(response) {
      $scope.team = response.data;
    }, function(response) {
      console.log(response);
    });
  };
  
  $scope.loadData();
  var promise = $interval($scope.loadData, 10000)
  $scope.$on('$destroy', function(){
    if (angular.isDefined(promise)) {
        $interval.cancel(promise);
        promise = undefined;
    }
  });
 
  $scope.sendMessage = function() {
    if($scope.chatMessage === undefined || $scope.chatMessage == null || $scope.chatMessage.length < 1)
      return;
    var args = {
      c: this.ctrl.person.team,
      n: this.ctrl.person.name,
      m: $scope.chatMessage
    };
    $http({
      method : 'GET',
      url : '/api/olq/postmessage',
      params: args
    }).then(function(response) {
      $scope.team = response.data;
      $scope.chatMessage = "";
    }, function(response) {
      console.log(response);
    });
  };
});

quizRunnerModule.component('teampanel', {
  templateUrl : 'components/team/page.ng.html',
  bindings : {
    person : '=',
    hidechrome : '='
  },
  controller : 'TeamNavController',
  controllerAs : 'ctrl'
});