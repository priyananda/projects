quizRunnerModule.controller('GuitarController', function($scope,
    $routeParams, $location, $http) {
  var canvas = new fabric.Canvas('canvas', {
    hoverCursor : 'pointer',
    selection : false,
    perPixelTargetFind : true,
    targetFindTolerance : 5
  });
  
  fabric.Image.fromURL('img/guitarbg.jpg', function(guitarBgImg) {
    canvas.add(guitarBgImg);
    canvas.sendToBack(guitarBgImg);
  });
  
  const songs = [
    {label: 'A#', audio: 'audio/left1.mp3', left: 200, top: 130 }
  ];
  
  songs.forEach(function(s) {
    var circle = new fabric.Circle({
      radius : 20,
      fill : '#eef',
      originX : 'center',
      originY : 'center'
    });

    var text = new fabric.Text(s.label, {
      fontSize : 20,
      originX : 'center',
      originY : 'center'
    });
    
    var songIcon = new fabric.Group([ circle, text ], {
      left : s.left,
      top : s.top,
      hasBorders : false,
      hasControls : false,
      audio: s.audio
    });
    canvas.add(songIcon);
    canvas.bringToFront(songIcon);
  });
  
  canvas.on('mouse:down', function(options) {
    if (options.target == null || options.target.type === "group") {
      $scope.selectedAudio = options.target.audio;
    }
    $scope.$apply();
  });
});

quizRunnerModule.component('guitar', {
  templateUrl : 'components/guitar/page.ng.html',
  controller : 'GuitarController',
  controllerAs : 'ctrl'
});