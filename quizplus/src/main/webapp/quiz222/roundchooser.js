quizRunnerModule
  .controller('RoundChooserController', function ($scope, $routeParams, $location, QuizState) {
	  $scope.updateLabels = function() {
		  switch($scope.selectedLang) {
		    case "CPP":
		    	$scope.round1Label = "std::deque<question>";
		    	$scope.round2Label = "std::stack<question>";
		    	$scope.round3Label = "std::unordered_map<std::string, question>";
		    	break;
		    case "JAVA":
		    	$scope.round1Label = "java.util.Deque<Question>";
		    	$scope.round2Label = "java.util.Stack<Question>";
		    	$scope.round3Label = "java.util.Hashmap<String, Question>";
		    	break;
		    case "C#":
		    	$scope.round1Label = "Nito.Deque<Question>";
		    	$scope.round2Label = "Systems.Collections.Generic.Stack<Question>";
		    	$scope.round3Label = "Systems.Collections.Generic.Dictionary<String, Question>";
		    	break;
		    case "ENG":
		    	$scope.round1Label = "Doubly Linked List";
		    	$scope.round2Label = "Stack";
		    	$scope.round3Label = "Hash Map";
		    	break;
		    case "LISP":
		    	$scope.round1Label = "()())()())()(()(";
		    	$scope.round2Label = "()()(())(()()()()()())";
		    	$scope.round3Label = "(((((()()()()))))))(())()";
		    	break;
		  }
	  };
	  $scope.selectedLang = "CPP";
	  $scope.updateLabels();
  });