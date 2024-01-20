export class Team {
  private id: number = 0;
  private score: number = 0;
  private static QUIZ_ID: string = "quiz-202401";

  constructor(id: number) {
    this.id = id;
  }

  getId() {
    return this.id;
  }
  getScore() {
    return this.score;
  }
  addToScore(val: number) {
    this.score = this.score + val;
    this.save();
  }
  save() {
    localStorage.setItem(
      Team.QUIZ_ID + "/team/" + this.id,
      this.score.toString());
  }
  load() {
    var val = localStorage.getItem(
      Team.QUIZ_ID + "/team/" + this.id);
    if (val != null) {
      this.score = Number.parseInt(val);
    } else {
      this.score = 0;
    }
  }
}