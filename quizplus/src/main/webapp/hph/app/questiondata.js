quizRunnerModule.factory('QuestionData', function() {
  var helper = {};
  
  // Easy
  const SCHOOL_OF_MAGIC = {
      key: "mxpe",
      title: "School of Magic",
      hint: "Match the first name with the last name. One is missing.",
      img_url: "img/school_of_magic.jpg",
      img_width: "543",
      img_height: "768"
  };
  const MERLINS_BEARD = {
      key: "this",
      title: "Merlin's Beard",
      hint: "What series is this from? What's missing?",
      img_url: "img/merlins_beard.jpg",
      img_width: "640",
      img_height: "640"
  };
  const RANSOM_NOTE = {
      key: "rnfa",
      title: "Missing!",
      hint: "Are all the words spelled right?",
      img_url: "img/ransom_note.jpg",
      img_width: "600",
      img_height: "1751",
  };
  const WHERES_REBECCA = {
      key: "dgez",
      title: "Where's Rebecca?",
      hint: "Retrace her steps to see where she is.",
      img_url: "img/wheres_rebecca.png",
      img_width: "576",
      img_height: "700",
  };
 
  // Medium
  const SOLAR_SORT = {
      key: "ejsh",
      title: "Solar Sort",
      is_solar: true,
      hint: "Are they in the right order?",
  };
  const CALL_ME_MAYBE = {
      key: "nvqw",
      title: "Call me maybe",
      is_phone: true,
      hint: "Find the two word phrase by calling people up."
  };
  const TRICK_TACK_TOE = {
      key: "mabc",
      title: "Trick Tac Toe",
      hint: "",
      is_trick_tac_toe: true,
  };
  const FACE_OFF = {
      key: "vghd",
      title: "Face Off",
      hint: "The two faces share something in common.",
      img_url: "img/faceoff.jpg",
      img_height: "1400",
      img_width: "400"
  };
  
  // Hard
  const JACK_AND_JILL = {
      key: "lurh",
      title: "Jack and Jill",
      img_url: "img/jack_and_jill.png",
      img_height: "642",
      img_width: "684",
      hint: "Complete the poem, and see what's different between the words.", 
  };
  const ISBN = {
      key: "gcfg",
      title: "India Sierra Bravo November",
      hint: "What could the 13 Digit Numbers mean? Look at the title for clues.",
      img_url: "img/crossword.png",
      img_height: "900",
      img_width: "741"
  };
  const INDIANA_JONES = {
      key: "bwgs",
      title: "Indiana Jones",
      hint: "What could 1981 and 2008 mean here?",
      img_url: "img/indiana_jones.png",
      img_height: "800",
      img_width: "600"
  };
  const ELEMENTARY = {
      key: "pahf",
      title: "Elementary",
      hint: "Use all the blue box elements to form a movie title",
      img_url: "img/elementary.png",
      img_height: "600",
      img_width: "700"
  };
  
  const QUESTION_BY_KEY = new Map([
    // Easy
    [SCHOOL_OF_MAGIC.key, SCHOOL_OF_MAGIC],
    [MERLINS_BEARD.key, MERLINS_BEARD],
    [RANSOM_NOTE.key, RANSOM_NOTE],
    [WHERES_REBECCA.key, WHERES_REBECCA],
    
    // Medium
    [SOLAR_SORT.key, SOLAR_SORT],
    [CALL_ME_MAYBE.key, CALL_ME_MAYBE],
    [TRICK_TACK_TOE.key, TRICK_TACK_TOE],
    [FACE_OFF.key, FACE_OFF],
    
    // Hard
    [JACK_AND_JILL.key, JACK_AND_JILL],
    [ISBN.key, ISBN],
    [INDIANA_JONES.key, INDIANA_JONES],
    [ELEMENTARY.key, ELEMENTARY],
  ]);
  
  const ARENA_BY_KEY = new Map([
    ["e", {
      bgImg: "img/abg-easy.jpg",
      backLoc: {l: 120, t: 400},
      puzzles: [
        {q: SCHOOL_OF_MAGIC, loc: {l: 520, t: 80}},
        {q: MERLINS_BEARD, loc: {l: 410, t: 190}},
        {q: RANSOM_NOTE, loc: {l: 530, t: 210}},
        {q: WHERES_REBECCA, loc: {l: 800, t: 80}},
      ]
    }],
    ["m", {
      bgImg: "img/abg-medium.jpg",
      backLoc: {l: 172, t: 363},
      puzzles: [
        {q: SOLAR_SORT, loc: {l: 660, t: 70}},
        {q: CALL_ME_MAYBE, loc: {l: 850, t: 390}},
        {q: TRICK_TACK_TOE, loc: {l: 333, t: 346}},
        {q: FACE_OFF, loc: {l: 135, t: 185}},
      ]
    }],
    ["h", {
      bgImg: "img/abg-hard.jpg",
      backLoc: {l: 232, t: 521},
      puzzles: [
        {q: JACK_AND_JILL, loc: {l: 204, t: 302}},
        {q: ISBN, loc: {l: 415, t: 210}},
        {q: INDIANA_JONES, loc: {l: 690, t: 124}},
        {q: ELEMENTARY, loc: {l: 845, t: 75}},
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