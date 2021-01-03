quizRunnerModule.controller('AntakshariController', function($scope,
    $routeParams, $location, $http) {
  $scope.leftSongs = [
    {letter: 'K', audio: 'audio/left1.mp3'},
    {letter: 'O', audio: 'audio/left2.mp3'},
    {letter: 'A', audio: 'audio/left3.mp3'},
    {letter: 'N', audio: 'audio/left4.mp3'},
    {letter: 'P', audio: 'audio/left5.mp3'},
  ];
  $scope.rightSongs = [
    {letter: 'U', audio: 'audio/right1.mp3'},
    {letter: 'R', audio: 'audio/right2.mp3'},
    {letter: 'A', audio: 'audio/right3.mp3'},
    {letter: 'O', audio: 'audio/right4.mp3'},
    {letter: 'N', audio: 'audio/right5.mp3'},
  ];
});

quizRunnerModule.component('antakshari', {
  templateUrl : 'components/antakshari/page.ng.html',
  controller : 'AntakshariController',
  controllerAs : 'ctrl'
});