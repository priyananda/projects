quizRunnerModule.factory('Storage', function($window) {
  var helper = {};

  helper.loadPlayers = function() {
    var playersAsString = $window.localStorage.getItem('squiz-players');
    if (playersAsString == null) {
      return [];
    }
    return JSON.parse(playersAsString);
  };

  helper.savePlayers = function(players) {
    $window.localStorage.setItem('squiz-players', JSON.stringify(players));
  };
  
  helper.clear = function() {
    $window.localStorage.clear();
  };

  return helper;
});