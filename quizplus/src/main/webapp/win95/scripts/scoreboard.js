quizRunnerModule
  .controller('ScoreBoardController', function ($scope, $mdMenu, QuizState) {
	ctrl = this;
	$scope.addToTeam = function(teamscore, delta) {
		teamscore.points += delta;
		QuizState.saveToLocalStorage();
	};
	$scope.clearStorage = function() {
		QuizState.clearLocalStorage();
	};
	$scope.showSnapMenu = function(event) {
		$mdMenu.open(event);
	};
	this.teamMenu = [{
		text: 'Add 10 Points',
	    click: function ($itemScope, $event, modelValue, text, $li) {
	      $scope.addToTeam($itemScope.teamscore, 10);
	    }
      },{
	    text: 'Add 5 Points',
	    click: function ($itemScope, $event, modelValue, text, $li) {
	      $scope.addToTeam($itemScope.teamscore, 5);
	    }
    }];
	this.navIcons = [{
        text: 'My Computer',
		icon: 'assets/desktop-icons/MyComputer.png'
	  },{
        text: 'Encarta',
		icon: 'assets/desktop-icons/encarta.jpg'
	  },{
        text: 'Internet',
		icon: 'assets/desktop-icons/InternetExplorer.png',
		link: '#/question/1' 
      },{
        text: 'WinAmp',
  		icon: 'assets/desktop-icons/winamp.png'
      },{
        text: 'Bhajans',
    	icon: 'assets/desktop-icons/Folder.png'
      },{
        text: 'AOL',
      	icon: 'assets/desktop-icons/Folder.png'
      },{
        text: 'AoE',
      	icon: 'assets/desktop-icons/Folder.png'
      }
	];
});

quizRunnerModule.component('scoreboard', {
  templateUrl: 'templates/scoreboard.ng.html',
  bindings: {
    scores: '='
  },
  controller: 'ScoreBoardController',
  controllerAs: 'ctrl'
});