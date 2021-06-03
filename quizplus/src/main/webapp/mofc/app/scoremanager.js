quizRunnerModule.factory('ScoreManager', function(Storage, QuestionData) {
  var helper = Storage.getScore();
  
  helper.getSolvedCount = function(){
   return helper.size; 
  };
  
  helper.isSolved = function(key){
    return helper.get(key) !== undefined; 
  };
  
  helper.solve = function(key){
    helper.set(key, 1);
    Storage.saveScore(helper);
  };
  
  helper.getAllSolved = function() {
    return helper.keys();
  };
  
  helper.oneFromEachRoom = function() {
    var ret = 
      (helper.has('1') || helper.has('2') || helper.has('3') || helper.has('4')) &&
      (helper.has('5') || helper.has('6') || helper.has('7') || helper.has('8')) &&
      (helper.has('9') || helper.has('10') || helper.has('11') || helper.has('12')) &&
      (helper.has('13') || helper.has('14') || helper.has('15') || helper.has('16'));
    return ret;
  };
  
  return helper;
});