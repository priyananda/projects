quizRunnerModule
  .controller('WinAmpController', function ($scope, $location, QuizState) {
	  $scope.goto = function(where){
			$location.path(where);
		};
	  $scope.playlists = [
		{
		  name: 'Kyunki Film bhi Kabhi Song Thi',
		  songs: [
			{name: 'Foo.mp3'},
			{name: 'Bar.mp3'},
		  ]
		},{
		  name: 'Duniya Ja Tel Lene',
		  songs: [
			{name: 'Xoo.mp3'},
			{name: 'PuS.mp3'},
		  ]
		}
	  ]
  });