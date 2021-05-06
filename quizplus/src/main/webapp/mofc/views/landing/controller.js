quizRunnerModule
  .controller('LandingPageController', function ($scope, $http, $location, Storage, QuestionData) {
    $scope.person = Storage.getPerson();
    $scope.score = Storage.getScore();
    $scope.classInput = [];
    $scope.persons = [
      {cls: "person-1", image: "img/person_1.png", link: "#/s/1", name: "Mr. Hewitt"},
      {cls: "person-2", image: "img/person_2.png", link: "#/s/2", name: "Lady Agatha"},
      {cls: "person-3", image: "img/person_3.png", link: "#/s/3", name: "Mr. Dyll"},
      {cls: "person-4", image: "img/person_4.png", link: "#/s/4", name: "Ms. Wanda"},
    ];
    $scope.statusIcons = [
      [{q:1}, {q:2}, {}, {q:3}, {q:4}, {q: 5}],
      [{q:16}, {is_image: true}, {q:6}],
      [{q:15}],
      [{}, {q:7}],
      [{q:14}, {q:8}],
      [{q:13}, {q:12}, {q:11}, {}, {q:10}, {q:9}],
    ];
    
    $scope.join = function(key) {
      if(this.nameInput === undefined || this.nameInput == null || this.nameInput.length < 1)
        return;
      $http({
        method : 'GET',
        url : '/api/hph/register',
        params: {'n': this.nameInput, 'c': this.classInput.join()}
      }).then(function(response) {
        $scope.person = response.data;
        $scope.$parent.person = response.data;
        Storage.savePerson($scope.person);
      }, function(response) {
        console.log(response);
      });
    };
    
    $scope.classSets = [
      {
        name: 'K & 1st',
        rooms: [
          {name: 'K(Ms Carpenter)'},
          {name: 'K(Ms Muro)'},
          {name: 'K(Mrs Williams)'},
          {name: '1st(Ms Chow)'},
          {name: '1st(Ms Friedman)'},
          {name: '1st(Mrs Girard)'},
          {name: '1st(Mrs Van Cleave)'},
        ]
      }, {
        name: '2nd & 3rd',
        rooms: [
          {name: '2nd(Mrs Hasty)'},
          {name: '2nd(Mrs Lucio)'},
          {name: '2nd(Mrs White)'},
          {name: '3rd(Mrs Amundsen)'},
          {name: '3rd(Mrs Daviscourt)'},
          {name: '3rd(Mrs Andrews)'},
        ]
      }, {
        name: '4th & 5th',
        rooms: [
          {name: '4th(Ms Acevedo)'},
          {name: '4th(Ms Hein)'},
          {name: '4th(Mr Valley)'},
          {name: '5th(Mrs Fraley)'},
          {name: '5th(Ms Van Den Bos)'},
        ]
      }, {
        name: 'PoQ & Q',
        rooms: [
          {name: '2/3Q(Mrs Jones)'},
          {name: '2/3Q(Ms Pozo)'},
          {name: '4/5Q(Dr Bowns)'},
          {name: '4/5Q(Ms Stanley)'},
          {name: 'PoQ(Mrs Walker)'},
        ]
      }
    ];
    
    $scope.goto = function (where) {
      $location.path(where);
    };
    
    $scope.isAnswered = function(key) {
      return ($scope.score.get(key) !== undefined);
    };
    
    $scope.showMenu = function($mdMenu, event) {
      $mdMenu(event);
    };
    
    $scope.addTeam = function(classroom) {
      this.classInput.push(classroom.name);
      $scope.$apply();
    };
  });