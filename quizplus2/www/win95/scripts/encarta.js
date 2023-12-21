quizRunnerModule
  .controller('EncartaController', function ($scope, $location, QuizState) {
    $scope.currentSlideIdx = 0;
    $scope.question = questionInfo[0];

    $scope.goto = function(where){
      $location.path(where);
    };
    $scope.isPrevDisabled = function() {
      return ($scope.currentSlideIdx <= 0);
    };
    $scope.isNextDisabled = function() {
      return ($scope.currentSlideIdx >= $scope.question.clues.length - 1);
    };
    $scope.renderSlide = function() {
      $scope.currentImage = $scope.getImagePath($scope.question.clues[$scope.currentSlideIdx]);
      $scope.videoUrl = $scope.getFullVideoUrl($scope.question.clues[$scope.currentSlideIdx]);
    };
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
    $scope.getImagePath = function(ows) {
      return imageInfo[ows.slideid - 1].url + "=s1024";
    };
    $scope.getFullVideoUrl = function(ows) {
      if (ows.vid === undefined || ows.vid == null)
        return undefined;
      var vurl = videoInfo[ows.vid - 1].ytid;
      var vstart = videoInfo[ows.vid - 1].start;
      return "https://www.youtube.com/embed/" + vurl + "?hl=en&fs=1&rel=0&autoplay=0&showinfo=0&start=" + vstart;
    };
    $scope.renderSlide();
  });