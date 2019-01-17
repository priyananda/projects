quizRunnerModule
  .controller('RoundsPageController', function ($scope, $routeParams, $location, QuizState) {
	  $scope.round_info = [
		{
			icon: "wiki",
			link: "#/wiki",
			title: "Pete's quiz on Wikipedia",
			display_link: "http://en.wikipedia.org/wiki/Petes_Quiz",
			snippet: "Pete's Quiz is the most popular page on Wikipedia"
		}, {
			icon: "yt",
			link: "#/yt",
			title: "Pete's quiz on YouTube",
			display_link: "http://youtube.com/Petes_Quiz",
			snippet: "Pete makes literally the best videos ever..."
		}, {
			icon: "ebay",
			link: "#/ebay",
			title: "Pete's quiz on Ebay",
			display_link: "http://ebay.com/Petes_Quiz",
			snippet: "Bid on the best Pete has to offer..."
		}, {
			icon: "ig",
			link: "#/ig",
			title: "Pete's quiz on Instagram",
			display_link: "http://instagram.com/@Pete",
			snippet: "#cool #pete #forgetthatwerefacebook"
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