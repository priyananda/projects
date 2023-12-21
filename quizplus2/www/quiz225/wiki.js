quizRunnerModule
  .controller('WikiPageController', function ($scope, $routeParams, $location, QuizState, $mdDialog) {
	  function DialogController($scope) {
		  // Nothing is needed here.
	  };
	  $scope.showAlert = function(ev) {
		  $mdDialog.show({
		      controller: DialogController,
		      templateUrl: 'quiz225/nag.ng.html',
		      parent: angular.element(document.body),
		      targetEvent: ev,
		      clickOutsideToClose:true,
		      fullscreen: false
		    });
	  };
  });