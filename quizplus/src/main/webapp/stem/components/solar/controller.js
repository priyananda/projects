quizRunnerModule.controller('SolarPanelController', function($scope,
    $routeParams, $location, $http) {
  fabric.Object.prototype.originX = fabric.Object.prototype.originY = 'center';
  var canvas = new fabric.Canvas('canvas', {
    hoverCursor : 'pointer',
    selection : false,
    perPixelTargetFind : true,
    targetFindTolerance : 5
  });
  var planet;
  var bodies = [];
  const ORBIT_RADIUS = 35;
  const ORBIT_OFFSET = 60;
  const PLANET_NAME = 'J';
  const MOON_NAMES = [
    'I', 'C', 'G', 'E'
  ];

  fabric.Image.fromURL('img/sun.png', function(sunImg) {
    canvas.add(sunImg);
    sunImg.center();
  });

  function createOrbit() {
    var orbit = new fabric.Circle({
      radius : ORBIT_RADIUS * 4 + ORBIT_OFFSET,
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
  }
  
  function animatePlanet(planet) {
    // rotate around canvas center
    var cx = canvas.getWidth() / 2,
        cy = canvas.getHeight() / 2,
        // randomize starting angle to avoid planets starting on one line
        startAngle = fabric.util.getRandomInt(-180, 0),
        endAngle = startAngle + 359;

    (function animate() {
      var duration = 8 * 20000;
      fabric.util.animate({
        startValue: startAngle,
        endValue: endAngle,
        duration: duration,

        // linear movement
        easing: function(t, b, c, d) { return c*t/d + b; },

        onChange: function(angle) {
          angle = fabric.util.degreesToRadians(angle);

          var radius = 4 * ORBIT_RADIUS + ORBIT_OFFSET;
          var x = cx + radius * Math.cos(angle);
          var y = cy + radius * Math.sin(angle);

          planet.set({ left: x, top: y }).setCoords();

		  canvas.renderAll();
        },
        onComplete: animate
      });
    })();
  }

  function animateMoon(planet, moon, moonIndex) {
    // rotate around the planet
    var startAngle = fabric.util.getRandomInt(-180, 0),
        endAngle = startAngle + 359;

    (function animate() {
      var duration = (moonIndex + 1 ) * 7000;
      fabric.util.animate({
        startValue: startAngle,
        endValue: endAngle,
        duration: duration,

        // linear movement
        easing: function(t, b, c, d) { return c*t/d + b; },

        onChange: function(angle) {
          angle = fabric.util.degreesToRadians(angle);

          var radius = (moonIndex + 1) * 30 + 15;
          var x = planet.left + radius * Math.cos(angle);
          var y = planet.top + radius * Math.sin(angle);

          moon.set({ left: x, top: y }).setCoords();

		  canvas.renderAll();
        },
        onComplete: animate
      });
    })();
  }

  function createBody(size, label) {
    var circle = new fabric.Circle({
      radius : size,
      fill : '#eef',
      originX : 'center',
      originY : 'center'
    });

    var text = new fabric.Text(label, {
      fontSize : size,
      originX : 'center',
      originY : 'center'
    });

    var body = new fabric.Group([ circle, text ], {
      left : canvas.getWidth() / 2 + 1 * ORBIT_RADIUS + ORBIT_OFFSET,
      top : canvas.getHeight() / 2,
      hasBorders : false,
      hasControls : false
    });
    canvas.add(body);
    bodies.push(body);
	return body;
  }

  createOrbit(); 
  planet = createBody(30, PLANET_NAME);
  animatePlanet(planet);
  planet.moons = [];
  for (var i = 0; i < 4; i++) {
    var moon = createBody(15, MOON_NAMES[i]);
    planet.moons.push(moon);
	animateMoon(planet, moon, i);
  }
  
  function selectBody(selectedBody) {
	if (selectedBody === null) {
	  $scope.selectedImg = null; 
	} else {
      $scope.selectedImg = "img/" + selectedBody.getObjects("text")[0].text + ".jpg";
    }
    bodies.forEach(function (body){
      var circle = body.getObjects("circle")[0];
      if (body == selectedBody) {
        circle.fill = '#778899';
      } else {
        circle.fill = '#eef';
      }
      circle.dirty = true;
      body.dirty = true; 
    });
  }
  
  canvas.on('mouse:down', function(options) {
    if (options.target == null || options.target.type === "group") {
      selectBody(options.target);
    } else {
      selectBody(null);
    }
    $scope.$apply();
  });
  
});

quizRunnerModule.component('solar', {
  templateUrl : 'components/solar/page.ng.html',
  controller : 'SolarPanelController',
  controllerAs : 'ctrl'
});