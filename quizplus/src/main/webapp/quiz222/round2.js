function showQuestion() {
}

function diagramInitR2(scope, element, attrs, location, quizState) {
    var $ = go.GraphObject.make;
    var myDiagram = $(go.Diagram, element[0], {
    	grid: $(go.Panel, "Grid",
                { gridCellSize: new go.Size(50, 50) },
                $(go.Shape, "LineH", { stroke: "lightgray" }),
                $(go.Shape, "LineV", { stroke: "lightgray" })
              ),
    	allowDrop: true,
    	nodeTemplate: $(go.Node, "Auto", {
             click: function(e, obj) {
            	 var r2state = quizState.getR2State();
            	 const qid = obj.part.key;
            	 if (r2state.stack[r2state.stack.length - 1] != qid) {
            		 return;
            	 }
            	 location.path('/r/2/q/' + obj.part.key);
            	 if (!scope.$$phase) {
             		scope.$apply();
       		  	 }
             },
           },
           $(go.Shape, "Rectangle",
             { fill: "lightblue", desiredSize: new go.Size(100, 50) },
             { portId: "", fromLinkable: true, toLinkable: true, cursor: "pointer" }),
           $(go.TextBlock, { margin: 3 }, new go.Binding("text", "key")),
           new go.Binding("position", "pos", go.Point.parse).makeTwoWay(go.Point.stringify)
        ),
        model: scope.model,
       "undoManager.isEnabled": true,
       contentAlignment: go.Spot.BottomCenter,
    });
    return myDiagram; 
}

function paletteInitR2(scope, element, attrs, route, quizState) {
	var $ = go.GraphObject.make;
	var myPalette = 
      $(go.Palette, element[0],
        {
          nodeTemplate: $(go.Node, "Auto",
        	{
              click: function(e, obj) {
            	quizState.pushTopicToStack(obj.part.Ud.topicIdx);
            	route.reload();
              }
            },
            $(go.Shape, "Rectangle",
              { fill: "lightgreen" },
              { portId: "", fromLinkable: true, toLinkable: true, cursor: "pointer" },
              new go.Binding("fill", "color")
              ),
            $(go.TextBlock, { margin: 3 }, new go.Binding("text", "key"))
         ),
         model: scope.model,
         contentAlignment: go.Spot.Center,
        });
	return myPalette;
}

quizRunnerModule
  .directive('goDiagramR2', function ($location, QuizState){
	  return {
        restrict: 'E',
        template: '<div></div>',  // just an empty DIV element
        replace: true,
        scope: { model: '=goModel' },
        link: function(scope, element, attrs){
        	diagramInitR2(scope, element, attrs, $location, QuizState);
        }
	  };
  });

quizRunnerModule
  .directive('goPaletteR2', function ($location, $route, QuizState){
	  return {
        restrict: 'E',
        template: '<div></div>',  // just an empty DIV element
        replace: true,
        scope: { model: '=goModel' },
        link: function(scope, element, attrs) {
        	paletteInitR2(scope, element, attrs, $route, QuizState);
        }
	  };
  });

quizRunnerModule
  .controller('Round2Controller', function ($scope, $routeParams, $location, QuizState) {
	  var r2state = QuizState.getR2State();
	  var keynodes = [];
	  for (var i = 0; i < r2topics.length; ++i) {
		  keynodes.push({key: r2topics[i].name, topicIdx: i})
	  }
	  var qnodes = [];
	  for (var i = 0; i < r2state.stack.length; ++i) {
		  qnodes.push({
			  key: r2state.stack[i].toString(),
			  color: "lightgreen",
			  pos: go.Point.stringify(new go.Point(80, 500 - i * 60))
		  });
	  }
	  $scope.topicModel = new go.GraphLinksModel(keynodes, []);
	  $scope.stackModel = new go.GraphLinksModel(qnodes, []);
  });