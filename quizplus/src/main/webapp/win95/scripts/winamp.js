quizRunnerModule
  .controller('WinAmpController', function ($scope, $location, QuizState) {
	  $scope.goto = function(where){
			$location.path(where);
		};
	  $scope.playlists = [{
		  name: 'Kyunki Film bhi Kabhi Song Thi',
		  songs: [
			  {name: 'Foo.mp3', src: '../test/q1audio.mp3'},
			  {name: 'Bar.mp3'},
		  ]
		},{
		  name: 'What year is it?',
		  songs: [
			  {name: 'Xoo.mp3', src: '../test/q1audio.mp3'},
			  {name: 'PuS.mp3'},
		  ]
		}
	  ];
	  $scope.setActive = function(song){
	    $scope.selectedSong = song.src;
	  };
  });