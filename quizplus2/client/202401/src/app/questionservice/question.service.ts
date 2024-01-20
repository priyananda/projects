import { Injectable } from '@angular/core';
import { Question } from './question';

@Injectable({
  providedIn: 'root'
})
export class QuestionService {
  private static NUM_QUESTIONS : number = 50;
  private questions: Question[] = [];

  constructor() {
    var a = [
      Question.DIFFICULTY_EASY,
      Question.DIFFICULTY_MEDIUM,
      Question.DIFFICULTY_HARD];

    for (var i = 0; i < QuestionService.NUM_QUESTIONS; ++i) {
      var q = new Question(
        i + 1,
        "This is the title for Question #" + i,
        "",
        Question.TYPE_BASIC,
        "17.2%",
        a[i % 3]);
      q.load();
      this.questions.push(q);
    }
  }

  getQuestions() {
    return this.questions;
  }

  getQuestion(id: number) {
    return this.questions[id - 1];
  }
}