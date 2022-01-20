quizRunnerModule.factory('Storage', function($window) {
  var helper = {};

  helper.getPerson = function() {
    var personAsString = $window.localStorage.getItem('mofc-person');
    if (personAsString == null) {
      return undefined;
    }
    return JSON.parse(personAsString);
  };

  helper.savePerson = function(person) {
    $window.localStorage.setItem('mofc-person', JSON.stringify(person));
  };
  
  helper.getScore = function() {
    var scoreAsString = $window.localStorage.getItem('mofc-score');
    var ret = new Map();
    if (scoreAsString != null) {
      var keys = JSON.parse(scoreAsString);
      keys.forEach(function(k){ ret.set(k, 1); });
    }
    return ret;
  };
  
  helper.saveScore = function(score) {
    $window.localStorage.setItem('mofc-score', JSON.stringify(Array.from(score.keys())));
  };
  
  helper.getChat = function() {
    var chatAsString = $window.localStorage.getItem('mofc-chat');
    if (chatAsString == null) {
      return undefined;
    }
    return JSON.parse(chatAsString); 
  };
  
  helper.saveChat = function(chat) {
    $window.localStorage.setItem('mofc-chat', JSON.stringify(chat));
  };
  
  helper.clear = function() {
    $window.localStorage.clear();
  };

  return helper;
});