var quizRunnerModule = angular.module('QuizRunnerModule', [ 'ngMaterial', 
    , 'ngRoute']); 

quizRunnerModule.config(function($sceProvider) {
  // Completely disable SCE. For demonstration purposes only!
  // Do not use in new projects or libraries.
  $sceProvider.enabled(false); 
});

quizRunnerModule.config(function($mdThemingProvider) {
  $mdThemingProvider.theme('default')
    .dark();
});