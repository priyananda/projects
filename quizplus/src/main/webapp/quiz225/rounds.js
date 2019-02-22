quizRunnerModule
  .controller('RoundsPageController', function ($scope, $routeParams, $location, QuizState) {
	  $scope.round_info = [
		{
			icon: "wiki",
			link: "#/wiki",
			title: "Pete's quiz on Wikipedia",
			display_link: "http://en.wikipedia.org/wiki/Petes_Quiz",
			snippet: "Where every question has [citation needed]"
		}, {
			icon: "yt",
			link: "#/yt",
			title: "Pete's quiz on YouTube",
			display_link: "http://youtube.com/Petes_Quiz",
			snippet: "Can't be worse than Youtube Rewind 2018 ..."
		}, {
			icon: "snap",
			link: "#/snap",
			title: "Avengers: Thanos Snaps Again",
			display_link: "http://marvel.com/AvengersPetefinityWar",
			snippet: "Just give us all your money, already"
		}, {
			icon: "ig",
			link: "#/ig",
			title: "Pete's quiz on Instagram",
			display_link: "http://instagram.com/@Pete",
			snippet: "#cool #pete #forgetthatwearefacebook"
		}, {
			icon: "netflix",
			link: "#/netflix",
			title: "Pete's quiz on Netflix",
			display_link: "http://netflix.com/Petes_Quiz",
			snippet: "We apologize for House of Cards S6"
		}, {
			icon: "ph",
			link: "#/pornhub",
			title: "Pete's quiz on PornHub",
			display_link: "http://pornhub.com/Petes_Dirtiest_Deeds_Part5",
			snippet: "Hot and steamy ..."
		},
	  ];
  });