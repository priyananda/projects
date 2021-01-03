quizRunnerModule.controller('PhoneController', function($scope, $routeParams,
    $location, $http) {
  ctrl = this;
  $scope.contacts = [ {
    name : "Ganesh Bhai",
    phone : "(122) 173 1729",
    audio : "audio/gaitonde.mp3",
    image : "img/ph-ganesh.jpg",
  }, {
    name : "Hercule Poirot",
    phone : "(836) 578 8278",
    audio : "audio/poirot.mp3",
    image : "img/ph-poirot.png",
  }, {
    name : "MI6 HQ",
    phone : "(733) 482 1921",
    audio : "audio/mi6.mp3",
    image : "img/ph-mi6.jpg",
  }, {
    name : "Austin Powers",
    phone : "(999) 696 9696",
    audio : "audio/austinpowers.mp3",
    image : "img/ph-austin.jpg",
  }, {
    name : "Niko Belic",
    phone : "(171) 222 1729",
    audio : "audio/nikobelic.mp3",
    image : "img/ph-belic.jpg",
  }, {
    name : "Ethan Hunt",
    phone : "(345) 482 1910",
    audio : "audio/ethanhunt.mp3",
    image : "img/ph-ethanhunt.jpg",
  }, {
    name : "Prof Indiana Jones",
    phone : "(332) 018 3732",
    audio : "audio/indianajones.mp3",
    image : "img/ph-jones.jpg",
  }, {
    name : "Jack Bauer",
    phone : "(212) 010 2161",
    audio : "audio/jackbauer.mp3",
    image : "img/ph-bauer.jpg",
  }, {
    name : "Prof Farnsworth",
    phone : "(123) 701 8821",
    audio : "audio/fansworth.mp3",
    image : "img/ph-farnsworth.jpg",
  }, {
    name : "Jack Ryan",
    phone : "(432) 123 7876",
    audio : "audio/jackryan.mp3",
    image : "img/ph-jackryan.jpg",
  }, {
    name : "Jason Bourne",
    phone : "(223) 343 4293",
    audio : "audio/bourne.mp3",
    image : "img/ph-bourne.jpg",
  }, {
    name : "Jack Reacher",
    phone : "(981) 211 8332",
    audio : "audio/reacher.mp3",
    image : "img/ph-reacher.jpg",
  }, {
    name : "Sherlock Holmes",
    phone : "(323) 173 8271",
    audio : "audio/sherlock.mp3",
    image : "img/ph-sherlock.jpg",
  }];
  $scope.phone2person = new Map();
  $scope.contacts.forEach(function(contact) {
    var key = contact.phone.replace(/\(|\)| /g, '');
    contact.key = key;
    $scope.phone2person.set(key, contact);
  });

  $scope.callPhone = function(e, numbers) {
    $scope.currentContact = $scope.phone2person.get(numbers);
  };

  this.finishCall = function() {
    $scope.currentContact = null;
    $scope.vm.numbers = null;
    $scope.$apply();
  };
  
  $scope.clickContact = function(contact) {
    if (!$scope.currentContact) {
      $scope.vm.numbers = contact.key;
    }
  };
});

quizRunnerModule.component('phone', {
  templateUrl : 'components/phone/page.ng.html',
  controller : 'PhoneController',
  controllerAs : 'ctrl'
});