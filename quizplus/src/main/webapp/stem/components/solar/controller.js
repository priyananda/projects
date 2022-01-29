quizRunnerModule.controller('SolarPanelController', function($scope,
    $routeParams, $location, $http) {
  fabric.Object.prototype.originX = fabric.Object.prototype.originY = 'center';
  var canvas = new fabric.Canvas('canvas', {
    hoverCursor : 'pointer',
    selection : false,
    perPixelTargetFind : true,
    targetFindTolerance : 5
  });
  var orbits = [];
  var planets_by_orbital = [];
  const ORBIT_RADIUS = 35;
  const ORBIT_OFFSET = 60;
  const PLANET_NAMES = [
    '\u263F', '\u2640', '\u2641', '\u2642', '\u2643', '\u2644', '\u2645', '\u2646',
  ];
  const CLUE_NAMES = [
    'B', 'Y', 'E', 'P', 'L', 'U', 'T', 'O',
  ];
  const JUMBLER = [
    7, 4, 5, 0, 1, 6, 3, 2
  ];

  fabric.Image.fromURL('img/sun.png', function(sunImg) {
    canvas.add(sunImg);
    sunImg.center();
  });

  function createOrbit(i) {
    var orbit = new fabric.Circle({
      radius : ORBIT_RADIUS * i + ORBIT_OFFSET,
      left : canvas.getWidth() / 2,
      top : canvas.getHeight() / 2,
      fill : '',
      stroke : 'rgba(0,192,255,0.5)',
      hasBorders : false,
      hasControls : false,
      lockMovementX : true,
      lockMovementY : true,
      index : i
    });
    canvas.add(orbit);
    orbits.push(orbit);
  }
  
  function animatePlanet(planet) {
    // rotate around canvas center
    var cx = canvas.getWidth() / 2,
        cy = canvas.getHeight() / 2,
        // randomize starting angle to avoid planets starting on one line
        startAngle = fabric.util.getRandomInt(-180, 0),
        endAngle = startAngle + 359;

    (function animate() {
      var duration = (planet.orbitalIndex + 1) * 20000;
      fabric.util.animate({
        startValue: startAngle,
        endValue: endAngle,
        duration: duration,

        // linear movement
        easing: function(t, b, c, d) { return c*t/d + b; },

        onChange: function(angle) {
          angle = fabric.util.degreesToRadians(angle);

          var radius = planet.orbitalIndex * ORBIT_RADIUS + ORBIT_OFFSET;
          var x = cx + radius * Math.cos(angle);
          var y = cy + radius * Math.sin(angle);

          planet.set({ left: x, top: y }).setCoords();

          // only render once
          if (planet.orbitalIndex === 7) {
            canvas.renderAll();
          }
        },
        onComplete: animate
      });
    })();
  }

  function createPlanet(orbitalIndex, planetIndex) {
    var circle = new fabric.Circle({
      radius : 20,
      fill : '#eef',
      originX : 'center',
      originY : 'center'
    });

    var text = new fabric.Text(PLANET_NAMES[planetIndex], {
      fontSize : 20,
      originX : 'center',
      originY : 'center'
    });

    var planet = new fabric.Group([ circle, text ], {
      left : canvas.getWidth() / 2 + orbitalIndex * ORBIT_RADIUS + ORBIT_OFFSET,
      top : canvas.getHeight() / 2,
      hasBorders : false,
      hasControls : false,
      planetIndex : planetIndex,
      orbitalIndex : orbitalIndex
    });
    canvas.add(planet);
    planets_by_orbital.push(planet);
    animatePlanet(planet);
  }

  for (var i = 0; i < 8; i++) {
    createOrbit(i); 
    createPlanet(i, JUMBLER[i]);
  }
  
  function selectPlanet(selectedPlanet) {
    $scope.selectedPlanet = selectedPlanet;
    planets_by_orbital.forEach(function (planet){
      var circle = planet.getObjects("circle")[0];
      if (planet == selectedPlanet) {
        circle.fill = '#778899';
      } else {
        circle.fill = '#eef';
      }
      circle.dirty = true;
      planet.dirty = true; 
    });
  }
  
  canvas.on('mouse:down', function(options) {
    if (options.target == null || options.target.type === "group") {
      selectPlanet(options.target);
    } else {
      selectPlanet(null);
    }
    $scope.$apply();
  });
  
  function fixText(planet) {
    var text = planet.getObjects("text")[0];
    if (planet.planetIndex === planet.orbitalIndex) {
      text.text = CLUE_NAMES[planet.orbitalIndex];
    } else {
      text.text = PLANET_NAMES[planet.planetIndex];
    }
    text.dirty = true;
    planet.dirty = true;
  }
  
  $scope.moveInner = function() {
    if ($scope.selectedPlanet == null || $scope.selectedPlanet.orbitalIndex === 0) {
      return;
    }
    swapPlanets($scope.selectedPlanet, planets_by_orbital[$scope.selectedPlanet.orbitalIndex - 1]);
  };
  
  $scope.moveOuter = function() {
    if ($scope.selectedPlanet == null || $scope.selectedPlanet.orbitalIndex === 7) {
      return;
    }
    swapPlanets($scope.selectedPlanet, planets_by_orbital[$scope.selectedPlanet.orbitalIndex + 1]);
  };
    
 function swapPlanets(thisPlanet, otherPlanet) {
    var temp = thisPlanet.planetIndex;
    thisPlanet.planetIndex = otherPlanet.planetIndex;
    otherPlanet.planetIndex = temp;
    fixText(thisPlanet);
    fixText(otherPlanet);
    selectPlanet(otherPlanet);
  };
});

quizRunnerModule.component('solar', {
  templateUrl : 'components/solar/page.ng.html',
  controller : 'SolarPanelController',
  controllerAs : 'ctrl'
});