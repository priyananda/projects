import { Injectable } from '@angular/core';
import { Question } from './question';

@Injectable({
  providedIn: 'root'
})
export class QuestionService {
  private questions: Question[] = [];

  constructor() {

    this.aq(1,  [1], 2);
    this.aq(2,  [3], 4);
    this.aq(3,  [5], 6);
    this.aq(4,  [7], 8);
    this.aq(5,  [9], 10);
    this.aq(6,  [11], 12);
    this.aq(7,  [13], 14);
    this.aq(8,  [15], 16);
    this.aq(9,  [17], 18, "rxxIG8ajl-w", "rxxIG8ajl-w");
    this.aq(10,  [19], 20);
    this.aq(11,  [21], 22);
    this.aq(12,  [23], 24);
    this.aq(13,  [25], 26);
    this.aq(14,  [27, 28, 29, 30, 31, 32], 33);
    this.aq(15,  [34], 35);
    this.aq(16,  [36], 37);
    this.aq(17,  [38], 39);
    this.aq(18,  [40], 41);
    this.aq(19,  [42], 43);
    this.aq(20,  [44], 45);
    this.aq(21,  [46], 47, "9lsgyGyrMhk");
    this.aq(22,  [48], 49);
    this.aq(23,  [50], 51);
    this.aq(24,  [52], 53);

    this.aq(25,  [54], 55, "LIbkWC9xgZY", "JcqGSHS0UjQ");
    this.aq(26,  [56], 57);
    this.aq(27,  [58], 59);
    this.aq(28,  [60], 61);
    this.aq(29,  [62], 63);
    this.aq(30,  [64], 65);
    this.aq(31,  [66], 67);
    this.aq(32,  [68], 69);
    this.aq(33,  [70], 71);
  }

  private aq(id: number, slides: number[], ans: number, qvideo?: string, avideo?: string) {
    var q = new Question(
      id,
      slides,
      ans, qvideo, avideo);
    q.load();
    this.questions.push(q);
  }

  getQuestions() {
    return this.questions;
  }

  getQuestion(id: number) {
    return this.questions[id - 1];
  }
}