quizRunnerModule.factory('QuestionData', function() {
  var helper = {};
  
  const Q1 = {
      key: "1",
      title: "School of Magic",
      hint: "Match the first name with the last name. One is missing.",
      img_url: "img/school_of_magic.jpg",
      img_width: "543",
      img_height: "768"
  };
  const Q2 = {
      key: "2",
      title: "Merlin's Beard",
      hint: "What series is this from? What's missing?",
      img_url: "img/merlins_beard.jpg",
      img_width: "640",
      img_height: "640"
  };
  const Q3 = {
      key: "3",
      title: "Missing!",
      hint: "Are all the words spelled right?",
      img_url: "img/ransom_note.jpg",
      img_width: "600",
      img_height: "1751",
  };
  const Q4 = {
      key: "4",
      title: "Where's Rebecca?",
      hint: "Retrace her steps to see where she is.",
      img_url: "img/wheres_rebecca.png",
      img_width: "576",
      img_height: "700",
  };
  const Q5 = {
      key: "5",
      title: "School of Magic",
      hint: "Match the first name with the last name. One is missing.",
      img_url: "img/school_of_magic.jpg",
      img_width: "543",
      img_height: "768"
  };
  const Q6 = {
      key: "6",
      title: "Merlin's Beard",
      hint: "What series is this from? What's missing?",
      img_url: "img/merlins_beard.jpg",
      img_width: "640",
      img_height: "640"
  };
  const Q7 = {
      key: "7",
      title: "Missing!",
      hint: "Are all the words spelled right?",
      img_url: "img/ransom_note.jpg",
      img_width: "600",
      img_height: "1751",
  };
  const Q8 = {
      key: "8",
      title: "Where's Rebecca?",
      hint: "Retrace her steps to see where she is.",
      img_url: "img/wheres_rebecca.png",
      img_width: "576",
      img_height: "700",
  };
  const Q9 = {
      key: "9",
      title: "School of Magic",
      hint: "Match the first name with the last name. One is missing.",
      img_url: "img/school_of_magic.jpg",
      img_width: "543",
      img_height: "768"
  };
  const Q10 = {
      key: "10",
      title: "Merlin's Beard",
      hint: "What series is this from? What's missing?",
      img_url: "img/merlins_beard.jpg",
      img_width: "640",
      img_height: "640"
  };
  const Q11 = {
      key: "11",
      title: "Missing!",
      hint: "Are all the words spelled right?",
      img_url: "img/ransom_note.jpg",
      img_width: "600",
      img_height: "1751",
  };
  const Q12 = {
      key: "12",
      title: "Where's Rebecca?",
      hint: "Retrace her steps to see where she is.",
      img_url: "img/wheres_rebecca.png",
      img_width: "576",
      img_height: "700",
  };
  const Q13 = {
      key: "13",
      title: "School of Magic",
      hint: "Match the first name with the last name. One is missing.",
      img_url: "img/school_of_magic.jpg",
      img_width: "543",
      img_height: "768"
  };
  const Q14 = {
      key: "14",
      title: "Merlin's Beard",
      hint: "What series is this from? What's missing?",
      img_url: "img/merlins_beard.jpg",
      img_width: "640",
      img_height: "640"
  };
  const Q15 = {
      key: "15",
      title: "Missing!",
      hint: "Are all the words spelled right?",
      img_url: "img/ransom_note.jpg",
      img_width: "600",
      img_height: "1751",
  };
  const Q16 = {
      key: "16",
      title: "Where's Rebecca?",
      hint: "Retrace her steps to see where she is.",
      img_url: "img/wheres_rebecca.png",
      img_width: "576",
      img_height: "700",
  };
 
  const QUESTION_BY_KEY = new Map([
    ["1", Q1], ["2", Q2], ["3", Q3], ["4", Q4],
    ["5", Q5], ["6", Q6], ["7", Q7], ["8", Q8],
    ["9", Q9], ["10", Q10], ["11", Q11], ["12", Q12],
    ["13", Q13], ["14", Q14], ["15", Q15], ["16", Q16],
  ]);
  
  const ARENA_BY_KEY = new Map([
    ["1", {
      bgImg: "img/vic_bedroom.jpg",
      personImg: "img/person_1.png",
      puzzles: [
        {q: Q1, loc: {l: 520, t: 80}},
        {q: Q2, loc: {l: 410, t: 190}},
        {q: Q3, loc: {l: 530, t: 210}},
        {q: Q4, loc: {l: 800, t: 80}},
      ]
    }],
    ["2", {
      bgImg: "img/vic_study.jpg",
      personImg: "img/person_2.png",
      puzzles: [
        {q: Q5, loc: {l: 660, t: 70}},
        {q: Q6, loc: {l: 850, t: 390}},
        {q: Q7, loc: {l: 333, t: 346}},
        {q: Q8, loc: {l: 135, t: 185}},
      ]
    }],
    ["3", {
      bgImg: "img/vic_office.jpg",
      personImg: "img/person_3.png",
      puzzles: [
        {q: Q9, loc: {l: 204, t: 302}}, 
        {q: Q10, loc: {l: 415, t: 210}},
        {q: Q11, loc: {l: 690, t: 124}},
        {q: Q12, loc: {l: 845, t: 75}},
      ]
    }],
    ["4", {
      bgImg: "img/vic_dining.jpg",
      personImg: "img/person_4.png",
      puzzles: [
        {q: Q13, loc: {l: 204, t: 302}},
        {q: Q14, loc: {l: 415, t: 210}},
        {q: Q15, loc: {l: 690, t: 124}},
        {q: Q16, loc: {l: 845, t: 75}},
      ]
    }],
  ]);
 
  helper.getContent = function(key) {
    return QUESTION_BY_KEY.get(key);
  };
  helper.getArena = function(setId) {
    return ARENA_BY_KEY.get(setId);
  };
  
  return helper;
});