quizRunnerModule.controller('ChatController', function($scope,
    $routeParams, $location, $http) {
  const CHAT_ROOM_BY_TEAM = [
    "",
    "-MSaS_pBLvtliUhCaXRF",
    "-MSaS_pEFn4rDTqC_Vl5",
    "-MSaS_pFyf-x1vC-nmYu",
    "-MSaS_pGxsbMihbIPL3q",
    "-MSaS_pGxsbMihbIPL3r",
    "-MSaS_pGxsbMihbIPL3s",
  ];
  var config = {
    apiKey: "AIzaSyBmEjEQU_3m8K4LjN2hXfN-yNLGauw1wGU",
    authDomain: "quizplus-1145.firebaseapp.com",
    databaseURL: "https://quizplus-1145-default-rtdb.firebaseio.com"
  };
  firebase.initializeApp(config);
  
  $scope.chatUser = {
    userId: $scope.ctrl.person.personid,
    userName: $scope.ctrl.person.name,
    avatar: "img/avatar.png"
  };
  $scope.chatRoom = CHAT_ROOM_BY_TEAM[$scope.ctrl.person.team];

  // Get a reference to the Firebase Realtime Database
  var chatRef = firebase.database().ref();

  // Create an instance of Firechat
  $scope.chat = new Firechat(chatRef);

  // Listen for authentication state changes
  firebase.auth().onAuthStateChanged(function(user) {
    if (user) {
      // If the user is logged in, set them as the Firechat user
      $scope.chat.setUser(user.uid, $scope.ctrl.person.name);
      $scope.chat.enterRoom($scope.chatRoom);
      $scope.chatUser.userId = user.uid;
    } else {
      // If the user is not logged in, sign them in anonymously
      firebase.auth().signInAnonymously().catch(function(error) {
        console.log("Error signing user in anonymously:", error);
      });
    }
  });
  
  $scope.chat.on('message-add', function(room, m) {
    $scope.messages.push({
      id: m.id,
      text: m.message,
      userName: m.name,
      userId: m.userId,
      avatar: "img/avatar.png",
      date: m.timestamp
    });
    $scope.$applyAsync();
  });

  $scope.sendMessage = function(m) {
    $scope.chat.sendMessage($scope.chatRoom, m.text, messageType='default')
  };
});

quizRunnerModule.component('chat', {
  templateUrl : 'components/chat/page.ng.html',
  controller : 'ChatController',
  controllerAs : 'ctrl',
  bindings : {
    person : '=',
  },
});

/*
      $scope.chat.createRoom("Team 1 Room", "public", function(roomId){console.log(roomId);});
      $scope.chat.createRoom("Team 2 Room", "public", function(roomId){console.log(roomId);});
      $scope.chat.createRoom("Team 3 Room", "public", function(roomId){console.log(roomId);});
      $scope.chat.createRoom("Team 4 Room", "public", function(roomId){console.log(roomId);});
      $scope.chat.createRoom("Team 5 Room", "public", function(roomId){console.log(roomId);});
      $scope.chat.createRoom("Team 6 Room", "public", function(roomId){console.log(roomId);});
*/
