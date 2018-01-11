//Define a plugin to provide data labels
function CustomChartRenderer(chartInstance, easing) {
    // To only draw at the end of animation, check for easing === 1
    var ctx = chartInstance.chart.ctx;
    chartInstance.data.datasets.forEach(function (dataset, i) {
      var meta = chartInstance.getDatasetMeta(i);
      if (!meta.hidden) {
        meta.data.forEach(function(element, index) {
          // Draw the text in black, with the specified font
          ctx.fillStyle = 'rgb(0, 0, 0)';
          var fontSize = 16;
          var fontStyle = 'normal';
          var fontFamily = 'Roboto';
          ctx.font = Chart.helpers.fontString(fontSize, fontStyle, fontFamily);
          // Just naively convert to string for now
          // <---- ADJUST TO DESIRED TEXT --->
          var dataString = dataset.data[index].indexLabel;
          // Make sure alignment settings are correct
          ctx.textAlign = 'center';
          ctx.textBaseline = 'middle';
          var padding = 5;
          var position = element.tooltipPosition();
          ctx.fillText(dataString, position.x, position.y - (fontSize / 2) - padding);
        });
      }
    });
  }

quizRunnerModule
  .config(['ChartJsProvider', function (ChartJsProvider) {
    Chart.plugins.register({
	 afterDatasetsDraw: CustomChartRenderer
	});

   }])
  .controller('QuestionChooserController', function ($scope, $location) {
	  $scope.options = {
		  title: {
			  text: "\u{1F3B6} \u{1F3B7} \u{1F3B8} Quiz 219 The Music Quiz \u{1F3B9} \u{1F3BA} \u{1F3BB}",
			  fontSize: 30,
			  fontFamily: "Roboto",
			  fontStyle: "italic",
			  display: true
		  },
	      scales: {
	        xAxes: [{
	          display: true,
	          scaleLabel: {
	        	  display: true,
	        	  labelString: "Western           <->            Eastern",
	        	  fontFamily: "Roboto",
	        	  fontSize: 20
	          },
	          ticks: {
	            max: 100,
	            min: 0,
	            stepSize: 10,
	            callback: function(value, index, values) { return ""; }
	          }
	        }],
	        yAxes: [{
	          display: true,
	          scaleLabel: {
	        	  display: true,
	        	  labelString: "Contemporary           <->              Classical",
	        	  fontFamily: "Roboto",
	        	  fontSize: 20
	          },
	          ticks: {
	            max: 100,
	            min: 0,
	            stepSize: 10,
	            callback: function(value, index, values) { return ""; }
	          }
	        }]
	      }
	    };
	  
	$scope.series = new Array();
	$scope.data = new Array();
	
	for (i = 0; i < questionInfo.length; ++i) {
		$scope.series.push(questionInfo[i].genre);
		$scope.data.push({
			id: questionInfo[i].id,
			indexLabel: questionInfo[i].genre,
			x: questionInfo[i].location[0],
			y: questionInfo[i].location[1],
			r: questionInfo[i].location[2]
		});
	}
	
	$scope.onClick = function (points, evt) {
		var activePoint = points[0];
		if (activePoint !== undefined) {
			//alert(activePoint._chart.data.datasets[activePoint._datasetIndex].data[activePoint._index].indexLabel);
			var qid = activePoint._chart.data.datasets[activePoint._datasetIndex].data[activePoint._index].id;
			$location.path('/question/' + qid);
  		    if (!$scope.$$phase) {
  		    	$scope.$apply();
  		    }
		}
	};
});
