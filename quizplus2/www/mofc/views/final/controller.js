quizRunnerModule.controller('FinalPageController', function($scope,
    QuestionData, ScoreManager, ChatManager, Storage, $mdDialog, $http) {
  $scope.person = Storage.getPerson();
  $scope.suspects = QuestionData.getSuspects();
  $scope.clues = Array.from(ScoreManager.getAllSolved(), function(q) {
    return {
      key : q,
      clue : QuestionData.getClue(q)
    };
  });
  $scope.retorts = [
    "I aint done nothing!",
    "Hah, these blatantly false accusations don't bother me",
    "This is outrageous!",
    "Please believe me - I'm innocent!"
  ];

  $scope.goTo = function(path) {
    $location.path(path);
  };

  $scope.isAnswered = function(key) {
    return (Storage.getScore().get(key) !== undefined);
  };
  
  $scope.accuse = function(suspectId) {
    if (suspectId === 2) {
      if ($scope.evidence === "2" || $scope.evidence === "6" ||
        $scope.evidence === "10" || $scope.evidence === "14") {
        $scope.showCorrect();
        return;
      }
    }
    ChatManager.addMessage(suspectId,
        $scope.retorts[suspectId - 1],
        $scope.suspects[suspectId - 1]);
  };
  
  $scope.showCorrect = function(){
    var alert = $mdDialog.alert()
      .title('Congrats, you\'ve captured the culprit!')
      .textContent("Lady Agatha is an imposter. The real Lady Agatha died 10 years ago, and the imposter stole "
          + "her identity to rob others.")
      .ok('Close');
    $mdDialog.show(alert);
    $http({
      method : 'GET',
      url : '/api/mofc/postanswer',
      params: {'k': "17", 'p' : $scope.person.pid, 'a' : 'AGATHA'}
    })
  };
});