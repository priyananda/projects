import { inject } from '@angular/core';
import {SlidesService} from './slides.service';

export class Question {
  private static QUIZ_ID: string = "quiz-202502";

  private id: number = 0;
  private contentSlideIds: number[] = [];
  private answerSlideId: number = 0;
  private isAnswered: boolean = false;
  private questionVideo: string = "";
  private answerVideo: string = "";
  private slidesService: SlidesService = inject(SlidesService);

  constructor(id: number,
      contentSlideId: number[],
      answerSlideId: number,
      questionVideo?: string,
      answerVideo?: string) {
    this.id = id;
    this.contentSlideIds = contentSlideId;
    this.answerSlideId = answerSlideId;
    this.questionVideo = questionVideo ?? "";
    this.answerVideo = answerVideo ?? "";
  }

  getContentImageUrls() {
    return this.contentSlideIds
      .map(v => this.slidesService.getSlideImage(v));
  }
  getAnswerImageUrl() {
    return this.slidesService.getSlideImage(this.answerSlideId);
  }
  getTitle() {
    return this.id;
  }
  getContentVideo() {
    return this.questionVideo;
  }
  getAnswerVideo() {
    return this.answerVideo;
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