quizRunnerModule.factory('Storage', function($window) {
  var helper = {};

  helper.get = function() {
    var personAsString = $window.localStorage.getItem('olq-person');
    if (personAsString == null) {
      return undefined;
    }
    return JSON.parse(personAsString);
  };

  helper.save = function(person) {
    $window.localStorage.setItem('olq-person', JSON.stringify(person));
  };

  return helper;
});