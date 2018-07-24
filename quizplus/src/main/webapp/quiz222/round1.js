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
                                $(go.TextBlock, { margin: 30, editable: false },
                                  new go.Binding("text", "name").makeTwoWay())
                              ),
                linkTemplate: $(go.Link,
                                { relinkableFrom: true, relinkableTo: true },
                                $(go.Shape),
                                $(go.Shape, { toArrow: "Standard", stroke: null, strokeWidth: 0 })
                              ),
                initialContentAlignment: go.Spot.Center,
                layout:
                    $(go.LayeredDigraphLayout,
                      { direction: 0, layerSpacing: 6, columnSpacing: 6, setsPortSpots: false }),
                "ModelChanged": updateAngular,
                "ChangedSelection": updateSelection,
                "undoManager.isEnabled": true,
                allowLink: false,
                allowMove: false,
                allowRelink: false,
                autoScale: go.Diagram.Uniform,
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
	  $scope.model = new go.GraphLinksModel(
	    [
          { key: 1, name: "Q1", color: "lightblue" },
          { key: 2, name: "Q2", color: "orange" },
          { key: 3, name: "Q3", color: "lightgreen" },
          { key: 4, name: "Q4", color: "pink" },
          { key: 5, name: "Q5", color: "pink" },
          { key: 6, name: "Q6", color: "pink" }
        ],
	    [
          { from: 1, to: 2 },
          { from: 2, to: 1 },
          { from: 2, to: 3 },
          { from: 3, to: 2 },
          { from: 3, to: 4 },
          { from: 4, to: 3 },
          { from: 4, to: 5 },
          { from: 5, to: 4 },
          { from: 5, to: 6 },
          { from: 6, to: 5 },
        ]);
	  $scope.model.selectedNodeData = null;
	  $scope.goToQuestion = function(qid) {
		  $location.path('/r/1/q/' + qid);
		  if (!$scope.$$phase) {
	    	$scope.$apply();
		  }
	  }
  });