quizRunnerModule
  .controller('ScoringPageController', function ($scope, $routeParams, $location, $http) {
    $scope.groups = [];
    $scope.startIndex = 1;
    var currIndex = 1;
    for (i = 0; i < 6; ++i) {
      $scope.groups.push({
        start: currIndex,
        end: currIndex + 9
      });
      currIndex += 10;
    }
    $scope.grid = [];
    for(r = 0; r < 10; ++r){
      var row = [];
      for (c = 0; c < 6; ++c) {
        row.push({
          r: r, c: c, a: null
        });
      }
      $scope.grid.push(row);
    }
    var setData = function(r, c, response) {
      $scope.grid[r][c].a = response;
    };
    
    var loadData = function(teamId, questionId, r, c) {
      $http({
        method : 'GET',
        url : '/api/olq/getanswers',
        params: {t: teamId, q: questionId}
      }).then(function(response) {
        setData(r,c, response.data);
      }, function(response) {
        console.log(response);
      });
    };
    
    $scope.onGroupChanged = function() {
      for (r = 0; r < 10; ++r) {
        for (c = 0; c < 6; ++c) {
          loadData(1 + c, $scope.startIndex + r, r, c);
        }
      }
    };
  });