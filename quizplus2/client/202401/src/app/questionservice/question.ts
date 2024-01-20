export class Question {
  public static TYPE_BASIC: string = 'Basic';
  public static TYPE_ALL_PLAY: string = 'All Play';
  public static TYPE_CONNECT: string = 'Connect';
  public static TYPE_AUDIO_VIDEO: string = 'Audio/Video';

  public static DIFFICULTY_EASY: string = 'Easy';
  public static DIFFICULTY_MEDIUM: string = 'Medium';
  public static DIFFICULTY_HARD: string = 'Hard';

  private static QUIZ_ID: string = "quiz-202401";

  private id: number = 0;
  private name: string = "";
  private imageUrl: string = "";
  private isAnswered: boolean = false;
  private type: string = Question.TYPE_BASIC;
  private acceptance: string = "";
  private difficulty: string = Question.DIFFICULTY_EASY;

  constructor(id: number,
      name: string,
      imageUrl: string,
      type: string,
      acceptance: string,
      difficulty: string) {
    this.id = id;
    this.name = name;
    this.imageUrl = imageUrl;
    this.type = type;
    this.acceptance = acceptance;
    this.difficulty = difficulty;
  }

  getId() {
    return this.id;
  }
  getImageUrl() {
    return this.imageUrl;
  }
  getType() {
    return this.type;
  }
  getName() {
    return this.name;
  }
  getAcceptance() {
    return this.acceptance;
  }
  getDifficulty() {
    return this.difficulty;
  }

  answer() {
    this.isAnswered = true;
    this.save();
  }
  save() {
    localStorage.setItem(
      Question.QUIZ_ID + "/question/" + this.id,
      this.isAnswered.toString());
  }
  load() {
    var val = localStorage.getItem(
      Question.QUIZ_ID + "/question/" + this.id);
    if (val != null && val == "true") {
      this.isAnswered = true;
    } else {
      this.isAnswered = false;
    }
  }
}