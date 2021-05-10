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
  }
  
  return helper;
});