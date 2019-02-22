quizRunnerModule
  .controller('YouTubeController', function ($scope, $routeParams, $location, QuizState) {
	  $scope.videos = [
		  {url: "https://www.youtube.com/embed/PxZ9rf9Jy18"}, //v2
		  {url: "https://www.youtube.com/embed/A_kvP8cU6rM"}, //v4
		  {url: "https://www.youtube.com/embed/06u-kUueldM"}, //v5
		  {url: "https://www.youtube.com/embed/YMIA4Kj7buU"}, //v6
		  {url: "https://www.youtube.com/embed/yn-DzhGW5AE",
			  answer_url: "https://youtu.be/hFlDnpbTNJs"}, // v7
	  ];
  });