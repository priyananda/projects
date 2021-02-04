quizRunnerModule.factory('Storage', function($window) {
  var helper = {};

  helper.getPerson = function() {
    var personAsString = $window.localStorage.getItem('jan21-person');
    if (personAsString == null) {
      return undefined;
    }
    return JSON.parse(personAsString);
  };

  helper.savePerson = function(person) {
    $window.localStorage.setItem('jan21-person', JSON.stringify(person));
  };
  
  helper.clear = function() {
    $window.localStorage.clear();
  };

  return helper;
});