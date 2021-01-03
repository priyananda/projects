quizRunnerModule.controller('TrickTacToeController', function($scope,
    $routeParams, $location, $http) {
  $scope.board = [
    [
      {is_coin_cell: false, style: "", value: ""},
      {is_coin_cell: false, style: "trick-exp-cell", value: "45\u00A2"},
      {is_coin_cell: false, style: "trick-exp-cell", value: "31\u00A2"},
      {is_coin_cell: false, style: "trick-exp-cell", value: "40\u00A2"},
      {is_coin_cell: false, style: "", value: ""},
    ], [
      {is_coin_cell: false, style: "trick-exp-cell", value: "36\u00A2"},
      {is_coin_cell: true, value: "1"},
      {is_coin_cell: true, value: "1"},
      {is_coin_cell: true, value: "1"},
      {is_coin_cell: false, style: "trick-act-cell trick-act-cell-wrong", value: "=3\u00A2"},
    ], [
      {is_coin_cell: false, style: "trick-exp-cell", value: "40\u00A2"},
      {is_coin_cell: true, value: "1"},
      {is_coin_cell: true, value: "1"},
      {is_coin_cell: true, value: "1"},
      {is_coin_cell: false, style: "trick-act-cell trick-act-cell-wrong", value: "=3\u00A2"},
    ], [
      {is_coin_cell: false, style: "trick-exp-cell", value: "40\u00A2"},
      {is_coin_cell: true, value: "1"},
      {is_coin_cell: true, value: "1"},
      {is_coin_cell: true, value: "1"},
      {is_coin_cell: false, style: "trick-act-cell trick-act-cell-wrong", value: "=3\u00A2"},
    ], [
      {is_coin_cell: false, style: "", value: ""},
      {is_coin_cell: false, style: "trick-act-cell trick-act-cell-wrong", value: "=3\u00A2"},
      {is_coin_cell: false, style: "trick-act-cell trick-act-cell-wrong", value: "=3\u00A2"},
      {is_coin_cell: false, style: "trick-act-cell trick-act-cell-wrong", value: "=3\u00A2"},
      {is_coin_cell: false, style: "", value: ""},
    ]
  ];
  
  function recalcTable() {
    $scope.allCorrect = true;
    for (i = 1; i < 4; ++i) {
      var rowSum = parseInt($scope.board[i][1].value) +
        parseInt($scope.board[i][2].value) +
        parseInt($scope.board[i][3].value);
      $scope.board[i][4].value = "=" + rowSum + "\u00A2";
      if (rowSum + "\u00A2" === $scope.board[i][0].value) {
        $scope.board[i][4].style = "trick-act-cell trick-act-cell-right";
      } else {
        $scope.board[i][4].style = "trick-act-cell trick-act-cell-wrong";
        $scope.allCorrect = false;
      }
      
      var colSum = parseInt($scope.board[1][i].value) +
        parseInt($scope.board[2][i].value) +
        parseInt($scope.board[3][i].value);
      $scope.board[4][i].value = "=" + colSum + "\u00A2";
      if (colSum + "\u00A2" === $scope.board[0][i].value) {
        $scope.board[4][i].style = "trick-act-cell trick-act-cell-right";
      } else {
        $scope.board[4][i].style = "trick-act-cell trick-act-cell-wrong";
        $scope.allCorrect = false;
      }
    }
  }
  
  $scope.changeCoin = function(cell) {
    switch (cell.value) {
      case "1": cell.value = "5"; break;
      case "5": cell.value = "10"; break;
      case "10": cell.value = "25"; break;
      case "25": cell.value = "1"; break;
    }
    recalcTable();
  };
});

quizRunnerModule.component('tricktactoe', {
  templateUrl : 'components/tricktactoe/page.ng.html',
  controller : 'TrickTacToeController',
  controllerAs : 'ctrl'
});