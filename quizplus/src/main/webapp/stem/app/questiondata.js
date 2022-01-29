quizRunnerModule.factory('QuestionData', function() {
  var helper = {};
  
  const MATCH_DATA_ANIMALS = {
      rows: [
        [
          {answer:"kitten", image:"img/cat.jpg", options: ["cub", "kitten", "catling"]},
          {answer:"cub", image:"img/bear.jpg", options: ["cub", "bearlet", "pup"]},
          {answer:"calf", image:"img/cow.jpg", options: ["cowbell", "coward", "calf"]},
        ],
        [
          {answer:"pup", image:"img/wolf.jpg", options: ["wolflet", "dog", "pup"]},
          {answer:"joey", image:"img/kangaroo.jpg", options: ["joey", "roo", "aussie"]},
          {answer:"cub", image:"img/tiger.jpg", options: ["tigerling", "cub", "sher"]},
        ],
        [
          {answer:"gosling", image:"img/goose.jpg", options: ["gooselet", "lil goose", "gosling"]},
          {answer:"piglet", image:"img/pig.jpg", options: ["cub", "piglet", "pingling"]},
          {answer:"kid", image:"img/goat.jpg", options: ["kid", "goatlet", "goatbaby"]},
        ],
      ],
      answer: "BABY"
  };
  const MEMORY_DATA_EASY = {
      rows: [
        [
          {image: "img/rey.png", k: "r"},
          {image: "img/vader.png", k: "v"},
          {image: "img/bb8.png", k: "b"},
          {image: "img/kyloren.png", k: "k"},
        ],
        [
          {image: "img/r2d2.png", k: "r2"},
          {image: "img/yoda.png", k: "y"},
          {image: "img/vader.png", k: "v"},
          {image: "img/yoda.png", k: "y"},
        ],
        [
          {image: "img/bb8.png", k: "b"},
          {image: "img/kyloren.png", k: "k"},
          {image: "img/rey.png", k: "r"},
          {image: "img/r2d2.png", k: "r2"},
        ],
      ],
      answer: "STARWARS"
  };
  const MEMORY_DATA_HARD = {
      rows: [
        [
          {image: "img/washington.jpg", k: "r"},
          {image: "img/harrisburg.jpg", k: "v"},
          {image: "img/newyork.jpg", k: "b"},
          {image: "img/helena.jpg", k: "k"},
        ],
        [
          {image: "img/lansing.jpg", k: "r2"},
          {image: "img/california.jpg", k: "y"},
          {image: "img/pennsylvania.jpg", k: "v"},
          {image: "img/sacramento.jpg", k: "y"},
        ],
        [
          {image: "img/albany.jpg", k: "b"},
          {image: "img/montana.jpg", k: "k"},
          {image: "img/olympia.jpg", k: "r"},
          {image: "img/michigan.jpg", k: "r2"},
        ],
      ],
      answer: "CAPITALS"
  };
  
  const Q1 = {
      key: "1",
      title: "Visiting Venus",
      hint: "Click on an image, and then click on where you think the other image is located",
      is_memory: true,
      memory_data: MEMORY_DATA_EASY
  };
  const Q2 = {
      key: "2",
      title: "Journey to Jupiter",
      hint: "Click on an image, and then click on where you think the other image is located",
      is_memory: true,
      memory_data: MEMORY_DATA_EASY
  };
  const Q3 = {
      key: "3",
      title: "So Long, Saturn",
      hint: "What do we call these animal babies?",
      is_match: true,
      match_data: MATCH_DATA_ANIMALS,
  };
  const Q4 = {
      key: "4",
      title: "Navigating Neptune",
      hint: "Maybe a mirror might help?",
      img_url: "img/mirror.jpg",
      img_width: "600",
      img_height: "600",
  };
  const Q5 = {
      key: "5",
      title: "Elementary",
      hint: "For each maze, check which entrance leads to the center.",
      img_url: "img/maze_2.png",
      img_width: "609",
      img_height: "440"
  };
  const Q6 = {
      key: "6",
      title: "Altered Carbon",
      img_url: "img/amongus.png",
      hint: "Imposters tend to lie.",
      img_width: "800",
      img_height: "592"
  };
  const Q7 = {
      key: "7",
      title: "Quick Reactions",
      hint: "Try different numbers",
      img_url: "img/numcode.png",
      img_width: "640",
      img_height: "356"
  };
  const Q8 = {
      key: "8",
      title: "Solve the Solvent",
      hint: "Find the block a character can be found in.",
      is_spotit: true,
  };
  const Q9 = {
      key: "9",
      title: "Resistance is Futile",
      hint: "How many Fire, Water, Lava blocks can there be?",
      is_minecraft: true
  };
  const Q10 = {
      key: "10",
      title: "Ohm My!",
      img_url: "img/anagrams.png",
      hint: "Try jumbling the words up.",
      img_width: "521",
      img_height: "636"
  };
  const Q11 = {
      key: "11",
      title: "Current Affairs",
      hint: "Google is your friend.",
      is_match: true,
      match_data: MATCH_DATA_ANIMALS,
  };
  const Q12 = {
      key: "12",
      title: "Re-volt-ing!",
      hint: "Hmm, what planets are these from?",
      img_url: "img/solarsort.png",
      img_width: "800",
      img_height: "330"
  };
  const Q13 = {
      key: "13",
      title: "Fermat's Last Theorem",
      hint: "One of them is a fake stone.",
      img_url: "img/wordsearch.png", 
      img_width: "500",
      img_height: "647"
  };
  const Q14 = {
      key: "14",
      title: "Long Division",
      hint: "You don't have to guess all the letters, just the ones in yellow",
      img_url: "img/codebreaker.png",
      img_width: "600",
      img_height: "692"
  };
  const Q15 = {
      key: "15",
      hint: "Alien Algebra",
      title: "Alien Algebra", 
      is_match: true,
      match_data: MATCH_DATA_ANIMALS
  };
  const Q16 = {
      key: "16",
      title: "Pie-thagoras",
      hint: "Google is your friend",
      is_memory: true,
      memory_data: MEMORY_DATA_EASY
  };
 
  const SECTION_1 = {
      cls: "section-1", image: "img/section_1.jpg", link: "#/s/1"
  };
  const SECTION_2 = {
      cls: "section-2", image: "img/section_2.jpg", link: "#/s/2"
  };
  const SECTION_3 = {
      cls: "section-3", image: "img/section_3.jpg", link: "#/s/3"
  };
  const SECTION_4 = {
      cls: "section-4", image: "img/section_4.jpg", link: "#/s/4"
  };
 
  const QUESTION_BY_KEY = new Map([
    ["1", Q1], ["2", Q2], ["3", Q3], ["4", Q4],
    ["5", Q5], ["6", Q6], ["7", Q7], ["8", Q8],
    ["9", Q9], ["10", Q10], ["11", Q11], ["12", Q12],
    ["13", Q13], ["14", Q14], ["15", Q15], ["16", Q16],
  ]);
  
  const ARENA_BY_KEY = new Map([
    ["1", {
      bgImg: "img/section_1_bg.jpg",
      puzzles: [
        {q: Q1, loc: {l: 30, t: 610}, icon: 'img/pz_1_3.png', doneIcon: 'img/pz_1_3_done.png'},
        {q: Q2, loc: {l: 60, t: 430}, icon: 'img/pz_1_4.png', doneIcon: 'img/pz_1_4_done.png'},
        {q: Q3, loc: {l: 530, t: 50}, icon: 'img/pz_1_2.png', doneIcon: 'img/pz_1_2_done.png'},
        {q: Q4, loc: {l: 800, t: 300}, icon: 'img/pz_1_1.png', doneIcon: 'img/pz_1_1_done.png'},
      ]
    }],
    ["2", {
      bgImg: "img/section_2_bg.jpg",
      puzzles: [
        {q: Q5, loc: {l: 100, t: 360}, icon: 'img/pz_2.png', doneIcon: 'img/pz_2_done.png'},
        {q: Q6, loc: {l: 400, t: 360}, icon: 'img/pz_2.png', doneIcon: 'img/pz_2_done.png'},
        {q: Q7, loc: {l: 600, t: 360}, icon: 'img/pz_2.png', doneIcon: 'img/pz_2_done.png'},
        {q: Q8, loc: {l: 900, t: 360}, icon: 'img/pz_2.png', doneIcon: 'img/pz_2_done.png'},
      ]
    }],
    ["3", {
      bgImg: "img/section_3_bg.jpg",
      puzzles: [
        {q: Q9,  loc: {l: 20, t: 120}, icon: 'img/pz_3.png', doneIcon: 'img/pz_3_done.png'}, 
        {q: Q10, loc: {l: 60, t: 260}, icon: 'img/pz_3.png', doneIcon: 'img/pz_3_done.png'},
        {q: Q11, loc: {l: 40, t: 400}, icon: 'img/pz_3.png', doneIcon: 'img/pz_3_done.png'},
        {q: Q12, loc: {l: 50, t: 540}, icon: 'img/pz_3.png', doneIcon: 'img/pz_3_done.png'},
      ]
    }],
    ["4", {
      bgImg: "img/section_4_bg.jpg", 
      puzzles: [
        {q: Q13, loc: {l: 100, t: 220}, icon: 'img/pz_4_3.png', doneIcon: 'img/pz_4_3_done.png'},
        {q: Q14, loc: {l: 300, t: 480}, icon: 'img/pz_4_4.png', doneIcon: 'img/pz_4_4_done.png'},
        {q: Q15, loc: {l: 500, t: 220}, icon: 'img/pz_4_2.png', doneIcon: 'img/pz_4_2_done.png'},
        {q: Q16, loc: {l: 700, t: 480}, icon: 'img/pz_4_1.png', doneIcon: 'img/pz_4_1_done.png'},
      ]
    }],
  ]);
 
  helper.getContent = function(key) {
    return QUESTION_BY_KEY.get(key);
  };
  helper.getArena = function(setId) {
    return ARENA_BY_KEY.get(setId);
  };
  helper.getSections = function() {
    return [SECTION_1, SECTION_2, SECTION_3, SECTION_4];
  };
  
  return helper;
});