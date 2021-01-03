quizRunnerModule.factory('QuestionData', function() {
  var helper = {};
  
  const SOLAR_SYSTEM = {
      key: "mxpe",
      title: "Solar Sort",
      is_solar: true,
      hint: "Are they in the right order?",
      thumbnail_image: "img/sun.png"
  };
  const CALL_ME_MAYBE = {
      key: "this",
      title: "Call me maybe",
      is_phone: true,
      thumbnail_image: "img/callme.png",
      hint: "Find the two word phrase by calling people up."
  };
  const ISBN = {
      key: "rnfa",
      title: "India Sierra Bravo November",
      thumbnail_image: "img/crossword_thumb.png",
      hint: "What could the 13 Digit Numbers mean? Look at the title for clues.",
      img_url: "img/crossword.png",
      img_height: "847",
      img_width: "1029"
  };
  const C_CODE_DECODE = {
      key: "vghd",
      title: "C Code Decode",
      is_code: true,
      thumbnail_image: "img/code.jpg",
      hint: "The meaning of life, universe and everything might help."
  };
  const APP_KA_SUROOR = {
      key: "ejsh",
      title: "App ka Suroor",
      thumbnail_image: "img/sun.png",
      hint: ""
  };
  const CLOSE_UP_ANTAKSHARI = {
      key: "nvqw",
      title: "Yeh Hai Antakshari, Close Up Antakshari",
      is_antakshari: true,
      thumbnail_image: "img/closeup.jpg",
      hint: "Arrange the songs in order."
  };
  const FACE_OFF = {
      key: "mabc",
      title: "Face ... Off",
      thumbnail_image: "img/faceoff_thumb.jpg",
      hint: "The two faces share something in common.",
      img_url: "img/faceoff.jpg",
      img_height: "1400",
      img_width: "400"
  };
  const CRASS_WORDS = {
      key: "dgez",
      title: "Crass Word Puzzle",
      thumbnail_image: "img/crassword-thumb.png",
      img_url: "img/crassword.png",
      img_height: "595",
      img_width: "600",
      hint: "", 
  };
  const QED = {
      key: "lurh",
      title: "QED",
      thumbnail_image: "img/qed-icon.png",
      hint: "Do the LHS and RHS share a common symbol?",
      img_url: "img/qed.png",
      img_height: "812",
      img_width: "714"
  };
  const SOLO = {
      key: "gcfg",
      title: "Solo",
      thumbnail_image: "img/sun.png",
      hint: "",
      is_guitar : true,
  };
  const MISSING = {
      key: "bwgs",
      title: "Missing!",
      thumbnail_image: "img/missing-icon.png",
      hint: "Look at the title of the puzzle for a clue.",
      img_url: "img/ransom.jpg",
      img_height: "1308",
      img_width: "486"
  };
  const BOOK_CRICKET = {
      key: "pahf",
      title: "Cricket ki Bhook",
      thumbnail_image: "img/cricket-thumb.png",
      hint: "Be bold and read the book!",
      is_cricket: true,
  };
  
  const QUESTION_BY_KEY = new Map([
    [SOLAR_SYSTEM.key, SOLAR_SYSTEM],
    [CALL_ME_MAYBE.key, CALL_ME_MAYBE],
    [C_CODE_DECODE.key, C_CODE_DECODE],
    [CLOSE_UP_ANTAKSHARI.key, CLOSE_UP_ANTAKSHARI],
    [FACE_OFF.key, FACE_OFF],
    [ISBN.key, ISBN],
    [APP_KA_SUROOR.key, APP_KA_SUROOR],
    [CRASS_WORDS.key, CRASS_WORDS],
    [QED.key, QED],
    [SOLO.key, SOLO],
    [MISSING.key, MISSING],
    [BOOK_CRICKET.key, BOOK_CRICKET],
    [CRASS_WORDS.key, CRASS_WORDS]
  ]);
  const QUESTION_BY_SET = [
    [SOLAR_SYSTEM, CALL_ME_MAYBE, C_CODE_DECODE, CLOSE_UP_ANTAKSHARI],
    [FACE_OFF, ISBN, QED, MISSING],
    [BOOK_CRICKET, CRASS_WORDS]
  ];
 
  helper.getContent = function(key) {
    return QUESTION_BY_KEY.get(key);
  };
  helper.getAllQuestions = function(setId) {
    return QUESTION_BY_SET[setId];
  };
  
  return helper;
});