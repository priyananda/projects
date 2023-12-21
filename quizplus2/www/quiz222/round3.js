function nodeClicked(evt) {
	
}

function diagramInitR3(scope, element, attrs, $location) {
    var $ = go.GraphObject.make;
    myDiagram = $(go.Diagram, element[0], {
    	allowDrop: true,
    	nodeTemplate: $(go.Node, "Auto",
           {
             click: nodeClicked,
             doubleClick: nodeClicked,
           },
           $(go.Shape, "Rectangle",
             { fill: "lightgray" },
             { portId: "", fromLinkable: true, toLinkable: true, cursor: "pointer" }),
           $(go.TextBlock, { margin: 3 }, new go.Binding("text", "key"))
        ),
       "undoManager.isEnabled": true
    });
    return myDiagram; 
}

function paletteInitR3(scope, element, attrs) {
	var $ = go.GraphObject.make;
	myPalette =
      $(go.Palette, element[0],
        {
          nodeTemplate: $(go.Node, "Auto",
        	{
              click: nodeClicked,
              doubleClick: nodeClicked,
            },
            $(go.Shape, "Rectangle",
              { fill: "lightgreen" },
              { portId: "", fromLinkable: true, toLinkable: true, cursor: "pointer" }),
            $(go.TextBlock, { margin: 3 }, new go.Binding("text", "key"))
         ),
         model: scope.model,
         contentAlignment: go.Spot.BottomCenter,
        });
}

quizRunnerModule
  .directive('goDiagramR3', function ($location){
	  return {
        restrict: 'E',
        template: '<div></div>',  // just an empty DIV element
        replace: true,
        scope: { model: '=goModel' },
        link: function(scope, element, attrs){
        	var myDiagram = diagramInitR3(scope, element, attrs);
            myDiagram.addDiagramListener("ExternalObjectsDropped", function (e) {
                e.subject.each(function(node) {
                	if (node.Ud.data !== undefined) {
                		if (node.Ud.data.kqid !== undefined) {
                			$location.path('/r/3/q/' + node.Ud.data.kqid);
                			if (!scope.$$phase) {
                        		scope.$apply();
                  		  	}
                		} else {
                			document.getElementById('message-div').innerHTML =
                				"<code>HashMap.get(key) failed due to " + node.Ud.data.msg;
                		}
                	}
                });
            });
        }
	  };
  });

quizRunnerModule
  .directive('goPaletteR3', function ($location){
	  return {
        restrict: 'E',
        template: '<div></div>',  // just an empty DIV element
        replace: true,
        scope: { model: '=goModel' },
        link: paletteInitR3
	  };
  });

quizRunnerModule
  .controller('Round3Controller', function ($scope, $routeParams, $location, QuizState) {
	  var r3state = QuizState.getR3State();
	  var keynodes = [];
	  for (var i = 0; i < r3keys.length; ++i) {
		  var shouldShow = true;
		  if (r3keys[i].kqid !== undefined) {
			  var qid = r3keys[i].kqid;
			  var qidStr = r3keys[i].kqid.toString();
			  if (r3state.has(qid) || r3state.has(qidStr)) {
				  shouldShow = false;
			  }
		  }
		  if (shouldShow) {
			  keynodes.push({key: r3keys[i].name, data: r3keys[i]});
		  }
	  }
	  $scope.model = new go.GraphLinksModel(keynodes, []);
  });