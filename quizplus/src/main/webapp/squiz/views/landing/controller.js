quizRunnerModule
  .controller('LandingPageController', function ($scope, $http, $location, Storage,
      $mdDialog) {
    $scope.selectedPlayerIdx = 0;
	$scope.players = Storage.loadPlayers();

    $scope.getIcon = function(f) {
      return 'img/avatar.png';
    };

	$scope.addPlayer = function(ev) {
	  var confirm = $mdDialog.prompt()
	      .title('Enter Player Name')
	      .textContent('')
	      .targetEvent(ev)
	      .ok('Add')
	      .cancel('Cancel');
      $mdDialog.show(confirm).then(function (pname) {
        $scope.players.push({
          name: pname,
          score: 0,
          idx: $scope.players.length
        });
		Storage.savePlayers($scope.players);
      }, function () {});
    };

	$scope.shuffle = function() {
	    for (let i = $scope.players.length - 1; i > 0; i--) {
	        const j = Math.floor(Math.random() * (i + 1));
	        [$scope.players[i], $scope.players[j]] = [$scope.players[j], $scope.players[i]];
	    }
		for (let i = 0; i < $scope.players.length; ++i) {
            $scope.players[i].idx = i;
        }
		Storage.savePlayers($scope.players);
	};

	$scope.getClass = function(p) {
      return (p.idx === $scope.selectedPlayerIdx)
		? 'player-item-selected'
		: 'player-item';
    };

    $scope.updateScore = function(player, delta) {
      player.score += delta;
	  Storage.savePlayers($scope.players);
    };

    $scope.nextPlayer = function() {
  	  $scope.selectedPlayerIdx++;
      if ($scope.selectedPlayerIdx >= $scope.players.length) {
        $scope.selectedPlayerIdx = 0;
      }
    };

    $scope.prevPlayer = function() {
  	  $scope.selectedPlayerIdx--;
      if ($scope.selectedPlayerIdx < 0) {
        $scope.selectedPlayerIdx = $scope.players.length - 1;
      }
    };
  });