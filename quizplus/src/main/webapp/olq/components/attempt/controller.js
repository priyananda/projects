quizRunnerModule.controller('AttemptPanelController', function($scope, $routeParams,
    $location, $http) {
  $scope.qid = $routeParams.id;

  $scope.loadData = function() {
    console.log("Loading data for team " + $scope.ctrl.person.team);
    $http({
      method : 'GET',
      url : '/api/olq/getanswers',
      params: {'t': $scope.ctrl.person.team, q: $scope.qid}
    }).then(function(response) {
      $scope.team = response.data;
    }, function(response) {
      console.log(response);
    });
  };
  
  $scope.loadData();
 
  $scope.submitAttempt = function() {
    var args = {
      t: this.ctrl.person.team,
      n: this.ctrl.person.name,
      a: $scope.answerText,
      q: $scope.qid
    };
    $http({
      method : 'GET',
      url : '/api/olq/postanswer',
      params: args
    }).then(function(response) {
      $scope.team = response.data;
      $scope.answerText = "";
    }, function(response) {
      console.log(response);
    });
  };
});

quizRunnerModule.component('attemptpanel', {
  templateUrl : 'components/attempt/page.ng.html',
  bindings : {
    person : '=',
    question : '='
  },
  controller : 'AttemptPanelController',
  controllerAs : 'ctrl'
});