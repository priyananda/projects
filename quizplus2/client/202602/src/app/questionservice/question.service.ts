import { Injectable } from '@angular/core';
import { Question } from './question';

@Injectable({
  providedIn: 'root'
})
export class QuestionService {
  private questions: Question[] = [];

  constructor() {
    this.aq(1,  [1, 2], 3);
    this.aq(2,  [4,5,6], 7);
    this.aq(3,  [8, 9], 10);
    this.aq(4,  [0], 0);
    this.aq(5,  [11], 12);
    this.aq(6,  [13], 14);
    this.aq(7,  [15], 16);
    this.aq(8,  [17], 18);
    this.aq(9,  [19, 20], 21);
    this.aq(10,  [22], 23);
    this.aq(11,  [24], 25);
    this.aq(12,  [26], 27);
    this.aq(13,  [28], 29);
    this.aq(14,  [30], 31);
    this.aq(15,  [32], 33);
    this.aq(16,  [34], 35);
    this.aq(17,  [36], 37);
    this.aq(18,  [38], 39);
    this.aq(19,  [40], 41);
    this.aq(20,  [42], 43);
    this.aq(21,  [44], 45);
    this.aq(22,  [46], 47);
    this.aq(23,  [48], 49);
    this.aq(24,  [50], 51);
    this.aq(25,  [52], 53);
    this.aq(26,  [54], 55);
    this.aq(27,  [56], 57);
    this.aq(28,  [58], 59);
    this.aq(29,  [60], 61);
    this.aq(30,  [62], 63);
    this.aq(31,  [64], 65);
    this.aq(32,  [66], 67);
    this.aq(33,  [68], 69);
    this.aq(34,  [70], 71);
    this.aq(35,  [72], 73);
    this.aq(36,  [74], 75);
    this.aq(37,  [76], 77);
    this.aq(38,  [78], 79);
    this.aq(39,  [80], 81);
    this.aq(40,  [82], 83);
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