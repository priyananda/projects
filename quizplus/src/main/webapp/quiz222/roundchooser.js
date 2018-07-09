quizRunnerModule
  .controller('RoundChooserController', function ($scope, $routeParams, $location, QuizState) {
	  $scope.updateLabels = function() {
		  switch($scope.selectedLang) {
		    case "CPP":
		    	$scope.round1Label = "std::deque<question>";
		    	$scope.round2Label = "absl::binary_tree<question>";
		    	$scope.round3Label = "pps::bipartite_graph<question>";
		    	$scope.round4Label = "std::unordered_map<std::string, question>";
		    	break;
		    case "JAVA":
		    	$scope.round1Label = "java.util.Deque<Question>";
		    	$scope.round2Label = "com.google.common.collect.BinaryTree<Question>";
		    	$scope.round3Label = "shenoy.pete.BipartiteGraph<Question>";
		    	$scope.round4Label = "java.util.Hashmap<Question>";
		    	break;
		    case "C#":
		    	$scope.round1Label = "Nito.Deque<Question>";
		    	$scope.round2Label = "Shenoy.Quiz.BinaryTree<Question>";
		    	$scope.round3Label = "Shenoy.Quiz.BipartiteGraph<Question>";
		    	$scope.round4Label = "Systems.Collections.Generic.Dictionary<String, Question>";
		    	break;
		    case "ENG":
		    	$scope.round1Label = "Doubly Linked List";
		    	$scope.round2Label = "Binary Tree";
		    	$scope.round3Label = "Bipartite Graph";
		    	$scope.round4Label = "Hash Map";
		    	break;
		    case "LISP":
		    	$scope.round1Label = "()())()())()(()(";
		    	$scope.round2Label = "()()(())(()()()()()())";
		    	$scope.round3Label = "((()))()(()()((())(";
		    	$scope.round4Label = "(((((()()()()))))))(())()";
		    	break;
		  }
	  };
	  $scope.selectedLang = "CPP";
	  $scope.updateLabels();
  });