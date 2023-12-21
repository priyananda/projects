let TITLES_BY_COMPANY = new Map();
TITLES_BY_COMPANY.set('MICROSOFT', [
  "Software Engineer",
  "Software Engineer II",
  "Senior Software Engineer",
  "Principal Software Engineer",
  "Partner Software Engineer",
  "Distinguished Engineer",
  "Technical Fellow"
]);
TITLES_BY_COMPANY.set('GOOGLE', [
  "Software Engineer II",
  "Software Engineer III",
  "Senior Software Engineer",
  "Staff Software Engineer",
  "Principal Software Engineer",
  "Distinguished Engineer",
  "Google Fellow"
]);

quizRunnerModule.controller('LadderController', function($scope) {
  $scope.levelItems = [];
  var titles = TITLES_BY_COMPANY.get($scope.ctrl.company);
  for (i = 6; i >= 0; --i) {
    $scope.levelItems.push({
      title: titles[i],
      css_class: (i > $scope.ctrl.level) ? 'ladder-level-plain' : 'ladder-level-done' 
    });
  }
});

quizRunnerModule.component('ladder', {
  templateUrl : 'components/ladder/page.ng.html',
  bindings : {
    company : '=',
    level : '='
  },
  controller : 'LadderController',
  controllerAs : 'ctrl'
});