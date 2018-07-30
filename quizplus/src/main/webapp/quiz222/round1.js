quizRunnerModule
  .directive('goDiagram', function ($location){
	  return {
        restrict: 'E',
        template: '<div></div>',  // just an empty DIV element
        replace: true,
        scope: { model: '=goModel' },
        link: function(scope, element, attrs) {
        	var $ = go.GraphObject.make;
            var diagram = $(go.Diagram, element[0], {
                nodeTemplate: $(go.Node, "Auto",
                				{ doubleClick: onDoubleClick },
                                new go.Binding("location", "loc", go.Point.parse).makeTwoWay(go.Point.stringify),
                                $(go.Shape, "RoundedRectangle", new go.Binding("fill", "color"),
                                  {
                                    portId: "", cursor: "pointer", strokeWidth: 2,
                                    fromLinkable: true, toLinkable: true,
                                    fromLinkableSelfNode: true, toLinkableSelfNode: true,
                                    fromLinkableDuplicates: true, toLinkableDuplicates: true
                                  }),
                                $(go.TextBlock, { margin: 10, editable: false },
                                  new go.Binding("text", "name").makeTwoWay())
                              ),
                linkTemplate: $(go.Link,
                                { relinkableFrom: true, relinkableTo: true },
                                $(go.Shape),
                                $(go.Shape, { toArrow: "Diamond", scale: 2}),
                                $(go.Shape, { fromArrow: "Diamond", scale: 2 }),
                                $(go.Panel, "Auto",
                                        $(go.Shape,  // the label background, which becomes transparent around the edges
                                          { fill: $(go.Brush, "Radial", { 0: "rgb(240, 240, 240)", 0.3: "rgb(240, 240, 240)", 1: "rgba(240, 240, 240, 0)" }),
                                            stroke: null }),
                                        $(go.TextBlock,  // the label text
                                          { textAlign: "center",
                                            font: "10pt helvetica, arial, sans-serif",
                                            stroke: "#555555",
                                            margin: 4 },
                                          new go.Binding("text", "text"))
                                )
                              ),
                initialContentAlignment: go.Spot.Center,
                layout:
                    $(go.CircularLayout,
                      { direction: go.CircularLayout.Clockwise,
                    	arrangement: go.CircularLayout.ConstantDistance,
                    	radius: 300}),
                "ModelChanged": updateAngular,
                "ChangedSelection": updateSelection,
                "undoManager.isEnabled": true,
                allowLink: false,
                allowMove: false,
                allowRelink: false,
                //autoScale: go.Diagram.Uniform,
            });
            function onDoubleClick(e, obj){
            	$location.path('/r/1/q/' + obj.part.key);
            	if (!scope.$$phase) {
            		scope.$apply();
      		  	}
            }
            function updateAngular(e) {
                if (e.isTransactionFinished) {
                  scope.$apply();
                }
            }
            function updateSelection(e) {
                diagram.model.selectedNodeData = null;
                var it = diagram.selection.iterator;
                while (it.next()) {
                  var selnode = it.value;
                  // ignore a selected link or a deleted node
                  if (selnode instanceof go.Node && selnode.data !== null) {
                    diagram.model.selectedNodeData = selnode.data;
                    break;
                  }
                }
                scope.$apply();
            }
            scope.$watch("model", function(newmodel) {
                var oldmodel = diagram.model;
                if (oldmodel !== newmodel) {
                  diagram.removeDiagramListener("ChangedSelection", updateSelection);
                  diagram.model = newmodel;
                  diagram.addDiagramListener("ChangedSelection", updateSelection);
                }
            });
            scope.$watch("model.selectedNodeData.name", function(newname) {
                if (!diagram.model.selectedNodeData) return;
                // disable recursive updates
                diagram.removeModelChangedListener(updateAngular);
                // change the name
                diagram.startTransaction("change name");
                // the data property has already been modified, so setDataProperty would have no effect
                var node = diagram.findNodeForData(diagram.model.selectedNodeData);
                if (node !== null) node.updateTargetBindings("name");
                diagram.commitTransaction("change name");
                // re-enable normal updates
                diagram.addModelChangedListener(updateAngular);
            });
        }
	  }
  });

quizRunnerModule
  .controller('Round1Controller', function ($scope, $routeParams, $location, QuizState) {
	  var r1state = QuizState.getR1State();
	  var qnodes = [];
	  var qlinks = [];
	  for (var i = 1; i <= 15; ++i) {
		  var effectiveColor = "lightgrey";
		  if (i == r1state.start || i == r1state.end){
			  effectiveColor = "lightgreen";
		  } else if (i < r1state.start || i > r1state.end) {
			  effectiveColor = "lightblue";
		  }
		  qnodes.push({key: i, name: "Q" + i, color: effectiveColor});
		  var effectiveText = "";
		  if (i < r1state.start || i >= r1state.end) {
			  effectiveText = linkInfo[i - 1];
		  }
		  if (i < 15) {
			  qlinks.push({from: i, to: i + 1, text: effectiveText});
		  }
	  }
	  $scope.model = new go.GraphLinksModel(qnodes, qlinks);
	  $scope.model.selectedNodeData = null;
	  $scope.goToQuestion = function(qid) {
		  $location.path('/r/1/q/' + qid);
		  if (!$scope.$$phase) {
	    	$scope.$apply();
		  }
	  }
  });