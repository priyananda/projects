quizRunnerModule.controller('AlgebraController', function($scope,
    $routeParams, $location, $http) {

  const NUM_TO_SYM = [
    '\u26B3', '\u26B4', '\u26B5', '\u26B6', '\u26B7',
	'\u26D8', '\u26D9', '\u26DA', '\u26DB', '\u26DC',
  ];
  console.log(NUM_TO_SYM[9]);
  const SYM_TO_NUM = new Map([
	[NUM_TO_SYM[0], 0], [NUM_TO_SYM[1], 1], [NUM_TO_SYM[2], 2], [NUM_TO_SYM[3], 3],
	[NUM_TO_SYM[4], 4], [NUM_TO_SYM[5], 5], [NUM_TO_SYM[6], 6], [NUM_TO_SYM[7], 7],
	[NUM_TO_SYM[8], 8], [NUM_TO_SYM[9], 9]
  ]);

  function shuffleArray(array) {
    for (var i = array.length - 1; i > 0; i--) {
        var j = Math.floor(Math.random() * (i + 1));
        var temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
    return array;
  }
  const OPTIONS = shuffleArray(NUM_TO_SYM.map((x) => x));
  $scope.cells = [];
  for (i = 0; i < 5; ++i) {
   var cell = {};
   if (i === 2) {
     cell.options = ['+', '-', '*'];
   } else {
     cell.options = OPTIONS;
   }
   $scope.cells.push(cell);
  }

  function getNum(sym) {
    return SYM_TO_NUM.get(sym);
  }
  function setSym(num) {
    if (num === 0)
      return NUM_TO_SYM[0];
    var ret = '';
    if (num < 0) {
      ret += "- "
      num = -num;
    }
    var digits = '';
    while (num != 0) {
      var digit = (num % 10);
      num = Math.floor(num / 10);
      digits = NUM_TO_SYM[digit] + digits;
    }
    return ret + digits;
  }

  $scope.evaluateState = function() {
    for (i = 0; i < 5; ++i) {
	  if ($scope.cells[i].value === undefined || $scope.cells[0].value === '' || $scope.cells[0].value === null)
	    return;
    }
    var val1 = getNum($scope.cells[0].value) * 10 + getNum($scope.cells[1].value);  
    var val2 = getNum($scope.cells[3].value) * 10 + getNum($scope.cells[4].value);
    var result = 0;
    switch ($scope.cells[2].value) {
      case '+': result = val1 + val2; break;
      case '-': result = val1 - val2; break;
      case '*': result = val1 * val2; break;
    }
    $scope.calculatedValue = setSym(result);
  };
 
});

quizRunnerModule.component('algebra', {
  templateUrl : 'components/algebra/page.ng.html',
  controller : 'AlgebraController',
  controllerAs : 'ctrl'
});