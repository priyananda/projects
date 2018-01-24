quizRunnerModule
  .controller('QuestionController', function ($scope, $routeParams, $location, QuizState) {
	$scope.qid = $routeParams.id;
	$scope.question = questionInfo[$routeParams.id - 1];
	$scope.currentSlideIdx = 0;
	$scope.goto = function(where){
		$location.path(where);
	};
	$scope.isShowingAnswer = function() {
		return $scope.currentSlideIdx < 0;
	};
	$scope.isPrevDisabled = function() {
		return $scope.isShowingAnswer() ||
			($scope.currentSlideIdx <= 0);
	};
	$scope.isNextDisabled = function() {
		return $scope.isShowingAnswer() ||
			($scope.currentSlideIdx >= $scope.question.clues.length - 1);
	};
	$scope.renderSlide = function() {
		if ($scope.isShowingAnswer()) {
			$scope.currentImage = $scope.getImagePath($scope.question.answer);
			$scope.videoUrl = $scope.getFullVideoUrl($scope.question.answer);
		} else {
			$scope.currentImage = $scope.getImagePath($scope.question.clues[$scope.currentSlideIdx]);
			$scope.videoUrl = $scope.getFullVideoUrl($scope.question.clues[$scope.currentSlideIdx]);
		}
	}
	$scope.next = function() {
		if (!$scope.isNextDisabled()) {
			$scope.currentSlideIdx = $scope.currentSlideIdx + 1;
			$scope.renderSlide();
		}
	};
	$scope.prev = function() {
		if (!$scope.isPrevDisabled()) {
			$scope.currentSlideIdx = $scope.currentSlideIdx - 1;
			$scope.renderSlide();
		}
	};
	$scope.showAnswer = function() {
		$scope.currentSlideIdx = -1;
		$scope.renderSlide();
		QuizState.closeQuestion($scope.qid);
	};
	$scope.getImagePath = function(ows) {
		return imageInfo[ows.slideid - 1].url + "=s1024";
	};
	$scope.getFullVideoUrl = function(ows) {
		if (ows.vid === undefined || ows.vid == null)
			return undefined;
		var vurl = videoInfo[ows.vid - 1].ytid;
		var vstart = videoInfo[ows.vid - 1].start;
		//return "http://www.youtube.com/v/" + vurl + "&hl=en&fs=1&rel=0&autoplay=0&showinfo=0&start=30";
		return "https://www.youtube.com/embed/" + vurl + "?hl=en&fs=1&rel=0&autoplay=0&showinfo=0&start=" + vstart;
	}
	
	$scope.renderSlide();
  });