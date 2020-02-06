quizRunnerModule.controller('ScoreBoardController', function($scope, $mdMenu,
		QuizState) {
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
	this.teamMenu = [ {
		text : '+ 10 Points',
		click : function($itemScope, $event, modelValue, text, $li) {
			$scope.addToTeam($itemScope.teamscore, 10);
		}
	}, {
		text : '+ 5 Points',
		click : function($itemScope, $event, modelValue, text, $li) {
			$scope.addToTeam($itemScope.teamscore, 5);
		}
	}, {
		text : '- 5 Points',
		click : function($itemScope, $event, modelValue, text, $li) {
			$scope.addToTeam($itemScope.teamscore, 5);
		}
	}, {
		text : '- 5 Points',
		click : function($itemScope, $event, modelValue, text, $li) {
			$scope.addToTeam($itemScope.teamscore, 5);
		}
	}];
	this.navIcons = [ {
		text : 'My Computer',
		icon : 'assets/desktop-icons/MyComputer.png'
	}, {
		text : 'Encarta',
		icon : 'assets/desktop-icons/encarta.jpg',
		link : '#/encarta'
	}, {
		text : 'Internet',
		icon : 'assets/desktop-icons/InternetExplorer.png',
		link : '#/yahoo'
	}, {
		text : 'WinAmp',
		icon : 'assets/desktop-icons/winamp.png',
		link : '#/winamp'
	}, {
		text : 'Bhajans',
		icon : 'assets/desktop-icons/Folder.png'
	}, {
		text : 'Crystal Maze',
		icon : 'assets/desktop-icons/cr-maze.jpeg',
		link : '#/crystal'
	}, {
		text : 'AoE',
		icon : 'assets/desktop-icons/Folder.png'
	} ];
});

quizRunnerModule.component('scoreboard', {
	templateUrl : 'templates/scoreboard.ng.html',
	bindings : {
		scores : '='
	},
	controller : 'ScoreBoardController',
	controllerAs : 'ctrl'
});