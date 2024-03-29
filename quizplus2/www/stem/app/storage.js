quizRunnerModule.factory('Storage', function($window) {
  var helper = {};

  helper.getPerson = function() {
    var personAsString = $window.localStorage.getItem('stem-person');
    if (personAsString == null) {
      return undefined;
    }
    return JSON.parse(personAsString);
  };

  helper.savePerson = function(person) {
    $window.localStorage.setItem('stem-person', JSON.stringify(person));
  };
  
  helper.getScore = function() {
    var scoreAsString = $window.localStorage.getItem('stem-score');
    var ret = new Map();
    if (scoreAsString != null) {
      var keys = JSON.parse(scoreAsString);
      keys.forEach(function(k){ ret.set(k, 1); });
    }
    return ret;
  };
  
  helper.saveScore = function(score) {
    $window.localStorage.setItem('stem-score', JSON.stringify(Array.from(score.keys())));
  };
  
  helper.clear = function() {
    $window.localStorage.clear();
  };

  return helper;
});