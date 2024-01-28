import { inject } from '@angular/core';
import {SlidesService} from './slides.service';

export class Question {
  public static TYPE_STRING: string = 'String';
  public static TYPE_DP: string = 'Dynamic Programming';
  public static TYPE_MAPS: string = 'Map';
  public static TYPE_ALGO: string = 'Algorithm';
  public static TYPE_HEAP: string = 'Heap';

  public static DIFFICULTY_EASY: string = 'Easy';
  public static DIFFICULTY_MEDIUM: string = 'Medium';
  public static DIFFICULTY_HARD: string = 'Hard';

  private static QUIZ_ID: string = "quiz-202401";

  private id: number = 0;
  private name: string = "";
  private contentSlideIds: number[] = [];
  private answerSlideId: number = 0;
  private isAnswered: boolean = false;
  private type: string = Question.TYPE_STRING;
  private acceptance: string = "";
  private difficulty: string = Question.DIFFICULTY_EASY;

  private slidesService: SlidesService = inject(SlidesService);

  constructor(id: number,
      name: string,
      type: string,
      acceptance: string,
      difficulty: string,
      contentSlideId: number[],
      answerSlideId: number) {
    this.id = id;
    this.name = name;
    this.type = type;
    this.acceptance = acceptance;
    this.difficulty = difficulty;
    this.contentSlideIds = contentSlideId;
    this.answerSlideId = answerSlideId;
  }

  getContentImageUrls() {
    return this.contentSlideIds
      .map(v => this.slidesService.getSlideImage(v));
  }
  getAnswerImageUrl() {
    return this.slidesService.getSlideImage(this.answerSlideId);
  }
  getType() {
    return this.type;
  }
  getTitle() {
    return this.id +". " + this.name;
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