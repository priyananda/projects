quizRunnerModule.controller('CodePadController', function($scope,
    $routeParams, $location, $http) {
  $scope.inputValue = 10;
  $scope.programOutput = "";
  
  $scope.runProgram = function(){
    var encoded_string = "WKBFSX";
    var decoded_string = "";
    for (var i = 0; i < encoded_string.length; i++) {
      var ch = encoded_string.charCodeAt(i);
      ch = (ch + $scope.inputValue - 65) % 26 + 97;
      decoded_string += String.fromCharCode(ch);
    }
    $scope.programOutput = decoded_string; 
  };
});

quizRunnerModule.component('codepad', {
  templateUrl : 'components/codepad/page.ng.html',
  controller : 'CodePadController',
  controllerAs : 'ctrl'
});