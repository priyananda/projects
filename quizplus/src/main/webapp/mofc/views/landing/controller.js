quizRunnerModule
  .controller('LandingPageController', function ($scope, $http, $location, Storage, QuestionData, $mdDialog) {
    $scope.person = Storage.getPerson();
    $scope.score = Storage.getScore();
    $scope.suspects = QuestionData.getSuspects();
    
    if (!$scope.person) { 
      $mdDialog.show({
        controller: DialogController,
        controllerAs: 'ctrl',
        templateUrl: 'views/landing/regn.ng.html',
        parent: angular.element(document.body),
        clickOutsideToClose: false,
      });
      $scope.person = Storage.getPerson();
    }
    
    $scope.goTo = function(path) {
      $location.path(path);
    };
    
    function DialogController($mdDialog) {
      ctrl = this;
      
      ctrl.classSets = [
        {
          name: 'K & 1st >',
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
          name: '2nd & 3rd >',
          rooms: [
            {name: '2nd(Mrs Hasty)'},
            {name: '2nd(Mrs Lucio)'},
            {name: '2nd(Mrs White)'},
            {name: '3rd(Mrs Amundsen)'},
            {name: '3rd(Mrs Daviscourt)'},
            {name: '3rd(Mrs Andrews)'},
          ]
        }, {
          name: '4th & 5th >',
          rooms: [
            {name: '4th(Ms Acevedo)'},
            {name: '4th(Ms Hein)'},
            {name: '4th(Mr Valley)'},
            {name: '5th(Mrs Fraley)'},
            {name: '5th(Ms Van Den Bos)'},
          ]
        }, {
          name: 'PoQ & Q >',
          rooms: [
            {name: '2/3Q(Mrs Jones)'},
            {name: '2/3Q(Ms Pozo)'},
            {name: '4/5Q(Dr Bowns)'},
            {name: '4/5Q(Ms Stanley)'},
            {name: 'PoQ(Mrs Walker)'},
          ]
        }
      ];
      
      ctrl.classInput = [];

      ctrl.register = function(key) {
        if(ctrl.nameInput === undefined || ctrl.nameInput == null || ctrl.nameInput.length < 1)
          return;
        $http({
          method : 'GET',
          url : '/api/mofc/register',
          params: {'n': ctrl.nameInput, 'c': ctrl.classInput.join()}
        }).then(function(response) {
          Storage.savePerson(response.data);
          $mdDialog.hide();
        }, function(response) {
          console.log(response);
        });
      };
      
      ctrl.showMenu = function($mdMenu, event) {
        $mdMenu(event);
      };
      
      ctrl.addTeam = function(classroom) {
        ctrl.classInput.push(classroom.name);
      };
    }

    $scope.goto = function (where) {
      $location.path(where);
    };
    
    $scope.isAnswered = function(key) {
      return ($scope.score.get(key) !== undefined);
    };
  });