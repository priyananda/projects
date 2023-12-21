quizRunnerModule.factory('QuestionData', function() {
  var helper = {};
  
  const MATCH_DATA_PLANETS = {
      rows: [
        [
          {answer:"(None)", image:"img/mercury.jpg", options: ["(None)", "Mooncury", "Phobos"]},
          {answer:"(None)", image:"img/venus.jpg", options: ["Venusino", "(None)", "Venison"]},
          {answer:"Luna", image:"img/earth.jpg", options: ["Luna", "(None)", "Io"]},
        ],
        [
          {answer:"Phobos", image:"img/mars.jpg", options: ["Musk", "Dinos", "Phobos"]},
          {answer:"Ganymede", image:"img/jupiter.jpg", options: ["Ganymede", "Iowa", "California"]},
          {answer:"Enceladus", image:"img/saturn.jpg", options: ["Saturnday", "Enceladus", "Lil Saturn"]},
        ],
        [
          {answer:"Ariel", image:"img/uranus.jpg", options: ["Belle", "Ariel", "Jasmine"]},
          {answer:"Triton", image:"img/neptune.jpg", options: ["Triton", "Titan", "Titania"]},
          {answer:"Chiron", image:"img/pluto.jpg", options: ["Plutonium", "Chiron", "Goofy"]},
        ],
      ],
      answer: "SATELLITES"
  };
  const MEMORY_DATA_EASY = {
      rows: [
        [
          {image: "img/as1.jpg", k: "r"},
          {image: "img/as2.jpg", k: "v"},
          {image: "img/as3.jpg", k: "b"},
          {image: "img/as4.jpg", k: "k"},
        ],
        [
          {image: "img/as5.jpg", k: "r2"},
          {image: "img/as6.jpg", k: "y"},
          {image: "img/as2.jpg", k: "v"},
          {image: "img/as6.jpg", k: "y"},
        ],
        [
          {image: "img/as3.jpg", k: "b"},
          {image: "img/as4.jpg", k: "k"},
          {image: "img/as1.jpg", k: "r"},
          {image: "img/as5.jpg", k: "r2"},
        ],
      ],
      answer: "ASTRONAUTS"
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
      is_solar: true,
  };
  const Q3 = {
      key: "3",
      title: "So Long, Saturn",
      hint: "Identify the moons of each of the planers",
      is_match: true,
      match_data: MATCH_DATA_PLANETS,
  };
  const Q4 = {
      key: "4",
      title: "Navigating Neptune",
      hint: "For each alien, select where in the grid you can find them.",
      is_spotit: true,
  };
  const Q5 = {
      key: "5",
      title: "Elementary",
      hint: "Form words using Element symbols, e.g. TiTaNIC",
      img_url: "img/elementary.jpg",
      img_width: "734",
      img_height: "750"
  };
  const Q6 = {
      key: "6",
      title: "Altered Carbon",
      img_url: "img/bruno.jpg",
      hint: "Some words seem to be misspelled.",
      img_width: "700",
      img_height: "588"
  };
  const Q7 = {
      key: "7",
      title: "Fanning the Flames",
      hint: "Think about what category we are in",
      img_url: "img/chemword.png",
      img_width: "600",
      img_height: "600"
  };
  const Q8 = {
      key: "8",
      title: "Solve the Solvent",
      hint: "Try different rations of Acids and Bases",
      is_solvent: true,
  };
  const Q9 = {
      key: "9",
      title: "Resistance is Futile",
      hint: "Find the resistance of each resistor, and see how you can map it to letters",
	  img_url: "img/resist.png",
      img_width: "700",
      img_height: "700"
  };
  const Q10 = {
      key: "10",
      title: "Ohm My!",
      img_url: "img/ohmmy.png",
      hint: "Identify these electric pioneers and use their last names to find another pioneer.",
      img_width: "600",
      img_height: "600"
  };
  const Q11 = {
      key: "11",
      title: "Current Affairs",
      img_url: "img/current.png",
      hint: "Assemble all the true statements and form the answer.",
      img_width: "607",
      img_height: "363"
  };
  const Q12 = {
      key: "12",
      title: "Re-volt-ing!",
      hint: "Keep track of happens to the voltage at each gate.",
      img_url: "img/revolt.png",
      img_width: "600",
      img_height: "600"
  };
  const Q13 = {
      key: "13",
      title: "Fermat's Last Theorem",
      hint: "What's left after you add and subtract those letters?",
      img_url: "img/fermat.png", 
      img_width: "700",
      img_height: "600"
  };
  const Q14 = {
      key: "14",
      title: "Wordle, but with numbers",
      hint: "Once you get a green box, you know the digit in that place",
      is_wordle: true,
  };
  const Q15 = {
      key: "15",
      hint: "A number subtracted from itself is always 0.",
      title: "Alien Algebra",
      is_algebra: true,
  };
  const Q16 = {
      key: "16",
      title: "Pie-thagoras",
      hint: "33% of MITTEN?",
	  img_url: "img/pie.png",
      img_width: "459",
      img_height: "700"      
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