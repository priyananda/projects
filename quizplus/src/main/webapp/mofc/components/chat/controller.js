quizRunnerModule.controller('ChatController', function($scope,
    $routeParams, $location, $http, ChatManager) {

  $scope.chatUser = {
    userId: $scope.ctrl.person.pid,
    userName: $scope.ctrl.person.name,
    avatar: "img/avatar.png"
  };
  $scope.messages = ChatManager.getMessages($scope.ctrl.suspect.id);
  
  $scope.sendMessage = function(m) {
    ChatManager.addMessage($scope.ctrl.suspect.id, m.text, {
      name: $scope.ctrl.person.name, image: "img/avatar.png"});
    if ($scope.ctrl.isanswer && $scope.ctrl.questionkey) {
      $http({
        method : 'GET',
        url : '/api/mofc/postanswer',
        params: {'k': $scope.ctrl.questionkey, 'p' : $scope.ctrl.person.pid, 'a' : m.text}
      }).then(
        function(response) {
          var isSuccess = (response.data.status == "Success");
          ChatManager.addMessage(
            $scope.ctrl.suspect.id,
            (isSuccess ? "You got it right!" : "That's not it, try again."),
            $scope.ctrl.suspect);
        },
        function(response) {
          console.log(response);
        });
    }
  };
});

quizRunnerModule.component('chat', {
  templateUrl : 'components/chat/page.ng.html',
  controller : 'ChatController',
  controllerAs : 'ctrl',
  bindings : {
    person : '=',
    suspect : '=',
    isanswer : '=',
    questionkey : '=',
  },
});
