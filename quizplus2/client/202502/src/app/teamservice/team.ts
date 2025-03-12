export class Score {
  public wins : number = 0;
  public draws: number = 0;
  public gf: number = 0;
  public ga: number = 0;
  getPts() {
    return this.wins * 3 + this.draws;
  }
  getGoalDiff() {
    return this.gf - this.ga;
  }
  win() {
    this.wins++;
  }
  undoWin() {
    if (this.wins > 0)
      this.wins--;
  }
  draw() {
    this.draws++;
  }
  undoDraw() {
    if (this.draws > 0)
      this.draws--;
  }
  goalFor() {
    this.gf++;
  }
  goalAgainst() {
    this.ga++;
  }
  save(prefix: string) {
    localStorage.setItem(prefix + "/score/w", this.wins.toString());
    localStorage.setItem(prefix + "/score/d", this.draws.toString());
    localStorage.setItem(prefix + "/score/gf", this.gf.toString());
    localStorage.setItem(prefix + "/score/ga", this.ga.toString());
  }
  load(prefix: string) {
    this.wins = this.loadVal(prefix + "/score/w");
    this.draws = this.loadVal(prefix + "/score/d");
    this.gf = this.loadVal(prefix + "/score/gf");
    this.ga = this.loadVal(prefix + "/score/ga");
  }
  compareTo(other: Score) {
    if (this.getPts() != other.getPts())
      return other.getPts() - this.getPts();
    return other.getGoalDiff() - this.getGoalDiff();
  }
  private loadVal(path: string) : number {
    var val = localStorage.getItem(path);
    if (val != null) {
      return Number.parseInt(val);
    }
    return 0;
  }
}

export class Team {
  private id: number = 0;
  private score: Score = new Score();
  private name: string = "";
  private static QUIZ_ID: string = "quiz-202502";

  constructor(id: number, name: string) {
    this.id = id;
    this.name = name;
  }

  getId() {
    return this.id;
  }
  getIcon() {
    return "assets/team" + this.id + ".png";
  }
  getName() {
    return this.name;
  }
  getScore() {
    return this.score;
  }
  save() {
    this.score.save(Team.QUIZ_ID + "/team/" + this.id);
  }
  load() {
    this.score.load(Team.QUIZ_ID + "/team/" + this.id);
  }
}