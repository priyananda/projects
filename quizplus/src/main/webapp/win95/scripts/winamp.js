quizRunnerModule
  .controller('WinAmpController', function ($scope, $location, QuizState) {
	  $scope.goto = function(where){
			$location.path(where);
		};
	  $scope.playlists = [{
		  name: 'Kyunki Film bhi Kabhi Song Thi',
		  songs: [
			  {name: 'Song -01 -Napster-vbr-160bps.mp3', src: 'assets/sounds/kf1.mp3'},
			  {name: 'Song -01 -Napster-vbr-160bps.mp3', src: 'assets/sounds/kf2.mp3'},
			  {name: 'Song -01 -Napster-vbr-160bps.mp3', src: 'assets/sounds/kf3.mp3'},
			  {name: 'Song -01 -Napster-vbr-160bps.mp3', src: 'assets/sounds/kf4.mp3'},
			  {name: 'Song -01 -Napster-vbr-160bps.mp3', src: 'assets/sounds/kf5.mp3'},
			  {name: 'Song -01 -Napster-vbr-160bps.mp3', src: 'assets/sounds/kf6.mp3'}
		  ]
		},{
		  name: 'What year is it?',
		  songs: [
		    {name: 'Song -01 -songs.pk-hq.mp3', src: 'assets/sounds/yr1.mp3'},
        {name: 'Song -02 -songs.pk-hq.mp3', src: 'assets/sounds/yr2.mp3'},
        {name: 'Song -03 -songs.pk-hq.mp3', src: 'assets/sounds/yr3.mp3'},
        {name: 'Song -04 -songs.pk-hq.mp3', src: 'assets/sounds/yr4.mp3'},
        {name: 'Song -05 -songs.pk-hq.mp3', src: 'assets/sounds/yr5.mp3'},
        {name: 'Song -06 -songs.pk-hq.mp3', src: 'assets/sounds/yr6.mp3'}
		  ]
		}
	  ];
	  $scope.setActive = function(song){
	    $scope.selectedSong = song.src;
	  };
  });