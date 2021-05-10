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
  const MATCH_DATA_SPOT = {};
  const MATCH_DATA_FORTNITE = {
      rows: [
        [
          {answer:"Hootenanny", video:"video/hootenanny.mp4", options: ["Hootenanny", "Angry Birds", "Hoobastank"]},
          {answer:"Jubilation", video:"video/jub.mp4", options: ["Yelling", "Jubilation", "Hands in the Air"]},
          {answer:"Floss", video:"video/floss.mp4", options: ["Brush", "Mouthwash", "Floss"]},
        ],
        [
          {answer:"Chicken", video:"video/chicken.mp4", options: ["Swimming", "Chicken", "Coward"]},
          {answer:"Dance Move", video:"video/dancemove.mp4", options: ["Scrubs", "Doodoo", "Dance Move"]},
          {answer:"Orange Justice", video:"video/orange.mp4", options: ["Orange Justice", "Green Justice", "Yellow Justice"]},
        ],
        [
          {answer:"Ride the Pony", video:"video/pony.mp4", options: ["Gangnam", "Psi Duck", "Ride the Pony"]},
          {answer:"Groove Jam", video:"video/groove.mp4", options: ["Groove Jam", "Napoleon", "Dynamite"]},
          {answer:"Fresh", video:"video/fresh.mp4", options: ["Carlton", "Fresh", "Bel Air"]},
        ],
      ],
      answer: "BATTLEROYALE"
  };
  const MATCH_DATA_MASCOTS = {
      rows: [
        [
          {answer:"Eagles", image:"img/franklin.png", options: ["Eagles", "Unicorns", "Meerkats"]},
          {answer:"Frogs", image:"img/thoreau.png", options: ["Bears", "Frogs", "Gorillas"]},
          {answer:"Eagles", image:"img/kirk.png", options: ["Seahawks", "Falcons", "Eagles"]},
        ],
        [
          {answer:"Jaguars", image:"img/juanita.png", options: ["Gophers", "Jaguars", "Badgers"]},
          {answer:"Seals", image:"img/sandburg.png", options: ["Seals", "Vikings", "Bears"]},
          {answer:"Bulldogs", image:"img/bell.png", options: ["Rebels", "Frogs", "Bulldogs"]},
        ],
        [
          {answer:"Snakes", image:"img/keller.png", options: ["Snakes", "Unicorns", "Lions"]},
          {answer:"Cheetahs", image:"img/lakeview.png", options: ["Whales", "Panthers", "Cheetahs"]},
          {answer:"Raccoons", image:"img/rosehill.png", options: ["Raccoons", "Lions", "Wombats"]},
        ],
      ],
      answer: "LWSD"
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
  const MEMORY_DATA_HARD = {};
  
  const Q1 = {
      key: "1",
      title: "Magic Maze",
      img_url: "img/maze_1.jpg",
      img_width: "485",
      img_height: "478"
  };
  const Q2 = {
      key: "2",
      title: "Remember Me?",
      is_memory: true,
      memory_data: MEMORY_DATA_EASY
  };
  const Q3 = {
      key: "3",
      title: "Little Animals",
      is_match: true,
      match_data: MATCH_DATA_ANIMALS,
  };
  const Q4 = {
      key: "4",
      title: "Reflections",
      img_url: "img/mirror.jpg",
      img_width: "600",
      img_height: "600",
  };
  const Q5 = {
      key: "5",
      title: "aMAZEing",
      img_url: "img/maze_2.png",
      img_width: "609",
      img_height: "440"
  };
  const Q6 = {
      key: "6",
      title: "Among Us",
      img_url: "img/amongus.png",
      img_width: "800",
      img_height: "592"
  };
  const Q7 = {
      key: "7",
      title: "Crack the Code",
      img_url: "img/numcode.png",
      img_width: "640",
      img_height: "356"
  };
  const Q8 = {
      key: "8",
      title: "Spot It",
      is_locked: true,
      is_match: true,
      match_data: MATCH_DATA_SPOT,
  };
  const Q9 = {
      key: "9",
      is_locked: true,
      title: "Minecraft",
      is_minecraft: true
  };
  const Q10 = {
      key: "10",
      title: "The Grams of Ana",
      img_url: "img/anagrams.png",
      img_width: "521",
      img_height: "636"
  };
  const Q11 = {
      key: "11",
      title: "Fortnite",
      is_match: true,
      match_data: MATCH_DATA_FORTNITE,
  };
  const Q12 = {
      key: "12",
      title: "Solar Sort",
      img_url: "img/solarsort.png",
      img_width: "800",
      img_height: "330"
  };
  const Q13 = {
      key: "13",
      title: "Fake Stones?",
      img_url: "img/wordsearch.png", 
      img_width: "500",
      img_height: "647"
  };
  const Q14 = {
      key: "14",
      title: "Code Breakers",
      img_url: "img/codebreaker.png",
      img_width: "600",
      img_height: "692"
  };
  const Q15 = {
      key: "15",
      title: "Match the Mascots!",
      is_match: true,
      match_data: MATCH_DATA_MASCOTS
  };
  const Q16 = {
      key: "16",
      title: "The Memory Remains",
      is_locked: true,
      is_memory: true,
      memory_data: MEMORY_DATA_HARD
  };
 
  const SUSPECT_1 = {
      cls: "person-1", image: "img/person_1.png", link: "#/s/1", name: "Mr. Hewitt",
      id: 1, h: "6' 1''", w: "190 lbs", hc: "Brown", "ec": "Brown"
  };
  const SUSPECT_2 = {
      cls: "person-2", image: "img/person_2.png", link: "#/s/2", name: "Lady Agatha",
      id: 2, h: "5' 10''", w: "155 lbs", hc: "Blonde", "ec": "Blue"
  };
  const SUSPECT_3 = {
      cls: "person-3", image: "img/person_3.png", link: "#/s/3", name: "Mr. Dyll",
      id: 3, h: "5' 7''", w: "135 lbs", hc: "Brunnette", "ec": "Black"
  };
  const SUSPECT_4 = {
      cls: "person-4", image: "img/person_4.png", link: "#/s/4", name: "Ms. Wanda",
      id: 4, h: "5' 3''", w: "102 lbs", hc: "Black", "ec": "Black"
  };
 
  const QUESTION_BY_KEY = new Map([
    ["1", Q1], ["2", Q2], ["3", Q3], ["4", Q4],
    ["5", Q5], ["6", Q6], ["7", Q7], ["8", Q8],
    ["9", Q9], ["10", Q10], ["11", Q11], ["12", Q12],
    ["13", Q13], ["14", Q14], ["15", Q15], ["16", Q16],
  ]);
  
  const CLUES_BY_KEY = new Map([
    ["1", "No sign of break-in, it must be an inside job."],
    ["2", "Lady Agatha's birth certificate says that she was born in 1802."],
    ["3", "Mr. Hewitt walks with a limp."],
    ["4", "Mr. Dyll used to work for a reputed solicitor, why was he fired?"],
    ["5", "Ms. Wanda doesn't seem to know where the salt is."],
    ["6", "You find a necklace, but it is made of fake stones."],
    ["7", "Lady Agatha just came from England a few months ago."],
    ["8", "Ms. Wanda once fainted when the power went out."],
    ["9", "Mr. Hewitt constantly grumbles about how big the yard is."],
    ["10", "What's this - a blonde wig? Who could it be?"],
    ["11", "Lady Agatha claims that she has been to Paris, but doesn't know it is in France."],
    ["12", "Mr. Hewitt dug a mysterious pit in the yard, and then covered it up."],
    ["13", "Ms. Wanda met with a man on Thursday night, but denied doing so."],
    ["14", "Blueprints of Peter Kirk's mansion? What's that doing here?"],
    ["15", "Lady Agatha is allergic to dogs."],
    ["16", "Mr. Dyll used to be an athlete at college."],
  ]);
  
  const ARENA_BY_KEY = new Map([
    ["1", {
      bgImg: "img/vic_bedroom.jpg",
      suspect: SUSPECT_1,
      puzzles: [
        {q: Q1, loc: {l: 380, t: 610}},
        {q: Q2, loc: {l: 410, t: 430}},
        {q: Q3, loc: {l: 530, t: 610}},
        {q: Q4, loc: {l: 740, t: 170}},
      ]
    }],
    ["2", {
      bgImg: "img/vic_study.jpg",
      suspect: SUSPECT_2,
      puzzles: [
        {q: Q5, loc: {l: 420, t: 200}},
        {q: Q6, loc: {l: 760, t: 430}},
        {q: Q7, loc: {l: 500, t: 520}},
        {q: Q8, loc: {l: 390, t: 570}},
      ]
    }],
    ["3", {
      bgImg: "img/vic_office.jpg",
      suspect: SUSPECT_3,
      puzzles: [
        {q: Q9, loc: {l: 835, t: 320}}, 
        {q: Q10, loc: {l: 425, t: 410}},
        {q: Q11, loc: {l: 700, t: 140}},
        {q: Q12, loc: {l: 425, t: 75}},
      ]
    }],
    ["4", {
      bgImg: "img/vic_dining.jpg",
      suspect: SUSPECT_4,
      puzzles: [
        {q: Q13, loc: {l: 845, t: 510}},
        {q: Q14, loc: {l: 415, t: 480}},
        {q: Q15, loc: {l: 690, t: 200}},
        {q: Q16, loc: {l: 845, t: 225}},
      ]
    }],
  ]);
 
  helper.getContent = function(key) {
    return QUESTION_BY_KEY.get(key);
  };
  helper.getArena = function(setId) {
    return ARENA_BY_KEY.get(setId);
  };
  helper.getSuspects = function() {
    return [SUSPECT_1, SUSPECT_2, SUSPECT_3, SUSPECT_4];
  };
  helper.getClue = function(key) {
    return CLUES_BY_KEY.get(key);
  };
  
  return helper;
});