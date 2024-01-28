import { Injectable } from '@angular/core';
import { Question } from './question';

@Injectable({
  providedIn: 'root'
})
export class QuestionService {
  private static NUM_QUESTIONS: number = 50;
  private questions: Question[] = [];

  constructor() {

    this.aq(1, "3 SUM", Question.TYPE_STRING, Question.DIFFICULTY_HARD, [1], 2);
    this.aq(2, "B Tree Traversal", Question.TYPE_HEAP, Question.DIFFICULTY_EASY, [3], 4);
    this.aq(3, "Measure Quantity II", Question.TYPE_STRING, Question.DIFFICULTY_MEDIUM, [5], 6);
    this.aq(4, "Multiple Substrings", Question.TYPE_MAPS, Question.DIFFICULTY_MEDIUM, [7], 8);
    this.aq(5, "Grey Code", Question.TYPE_HEAP, Question.DIFFICULTY_MEDIUM, [9], 10);
    this.aq(6, "Unary to Binary", Question.TYPE_STRING, Question.DIFFICULTY_MEDIUM, [11], 12);
    this.aq(7, "Hash Collision", Question.TYPE_MAPS, Question.DIFFICULTY_HARD, [13], 14);
    this.aq(8, "Missing Integer in Array", Question.TYPE_ALGO, Question.DIFFICULTY_EASY, [15], 16);
    this.aq(9, "Modify one element in Array", Question.TYPE_HEAP, Question.DIFFICULTY_MEDIUM, [17], 18);
    this.aq(10, "Lexicographically Complete", Question.TYPE_DP, Question.DIFFICULTY_EASY, [19, 20, 21], 22);
    this.aq(11, "Double Standards", Question.TYPE_HEAP, Question.DIFFICULTY_MEDIUM, [23], 24);
    this.aq(12, "Shell Sort", Question.TYPE_STRING, Question.DIFFICULTY_MEDIUM, [25], 26);
    this.aq(13, "Blank Find II", Question.TYPE_STRING, Question.DIFFICULTY_EASY, [27, 28], 29);
    this.aq(14, "Alternative Permutations", Question.TYPE_HEAP, Question.DIFFICULTY_HARD, [30], 31);
    this.aq(15, "Right to Left I", Question.TYPE_STRING, Question.DIFFICULTY_EASY, [32], 33);
    this.aq(16, "Right to Left II", Question.TYPE_HEAP, Question.DIFFICULTY_MEDIUM, [34], 35);
    this.aq(17, "Name Collision", Question.TYPE_MAPS, Question.DIFFICULTY_EASY, [36], 37);
    this.aq(18, "Third element in Array", Question.TYPE_HEAP, Question.DIFFICULTY_MEDIUM, [38], 39);
    this.aq(19, "Detect Cycles in Graph", Question.TYPE_ALGO, Question.DIFFICULTY_HARD, [40], 41);
    this.aq(20, "Best element in array", Question.TYPE_DP, Question.DIFFICULTY_EASY, [42, 43, 44], 45);
    this.aq(21, "Pyrotechnic Initiation", Question.TYPE_STRING, Question.DIFFICULTY_EASY, [46], 47);
    this.aq(22, "Silent Intervals", Question.TYPE_ALGO, Question.DIFFICULTY_MEDIUM, [48], 49);
    this.aq(23, "Degrees of Freedom", Question.TYPE_HEAP, Question.DIFFICULTY_EASY, [50], 51);
    this.aq(24, "Graph Cover", Question.TYPE_MAPS, Question.DIFFICULTY_MEDIUM, [52], 53);

    this.aq(25, "Total ways to fail", Question.TYPE_HEAP, Question.DIFFICULTY_MEDIUM, [54], 55);
    this.aq(26, "Decreased Visibility", Question.TYPE_STRING, Question.DIFFICULTY_EASY, [56], 57);
    this.aq(27, "Cross Product", Question.TYPE_STRING, Question.DIFFICULTY_EASY, [58], 59);
    this.aq(28, "Coordinate transformation", Question.TYPE_ALGO, Question.DIFFICULTY_HARD, [60], 61);
    this.aq(29, "Elliptic Curves", Question.TYPE_HEAP, Question.DIFFICULTY_EASY, [62], 63);
    this.aq(30, "Bipartite Graph", Question.TYPE_DP, Question.DIFFICULTY_MEDIUM, [64], 65);
    this.aq(31, "Disjoint Set", Question.TYPE_HEAP, Question.DIFFICULTY_EASY, [66], 67);
    this.aq(32, "Remove orphan child nodes", Question.TYPE_HEAP, Question.DIFFICULTY_MEDIUM, [68], 69);
    this.aq(33, "2D Array Search", Question.TYPE_ALGO, Question.DIFFICULTY_HARD, [70], 71);
    this.aq(34, "Path Traversal in 2D Grid", Question.TYPE_HEAP, Question.DIFFICULTY_MEDIUM, [72], 73);
    this.aq(35, "Ray Tracing", Question.TYPE_ALGO, Question.DIFFICULTY_EASY, [74], 75);
    this.aq(36, "Visibile Environment II", Question.TYPE_STRING, Question.DIFFICULTY_HARD, [76], 77);
    this.aq(37, "Find next string", Question.TYPE_ALGO, Question.DIFFICULTY_MEDIUM, [78], 79);
    this.aq(38, "Disconnected node in partitioned Graph", Question.TYPE_MAPS, Question.DIFFICULTY_EASY, [80], 81);
    this.aq(39, "Impersonated Characters", Question.TYPE_STRING, Question.DIFFICULTY_MEDIUM, [82], 83);
    this.aq(40, "64 bit union find", Question.TYPE_DP, Question.DIFFICULTY_EASY, [84, 85, 86], 87);
    this.aq(41, "Union of multiple states", Question.TYPE_STRING, Question.DIFFICULTY_EASY, [88], 89);
    this.aq(42, "Oct Tree Traversal", Question.TYPE_MAPS, Question.DIFFICULTY_HARD, [90], 91);
    this.aq(43, "Incorrect Differences", Question.TYPE_DP, Question.DIFFICULTY_EASY, [92], 92);
    this.aq(44, "Graph Isomorphism", Question.TYPE_STRING, Question.DIFFICULTY_MEDIUM, [93], 94);
    this.aq(45, "Literal Translation III", Question.TYPE_MAPS, Question.DIFFICULTY_MEDIUM, [95], 96);
    this.aq(46, "Trie of depth 5", Question.TYPE_DP, Question.DIFFICULTY_HARD, [97], 97);
    this.aq(47, "Missing numbers in array", Question.TYPE_MAPS, Question.DIFFICULTY_MEDIUM, [98], 99);
  }

  private aq(id: number, title: string, type: string,
    diff: string, slides: number[], ans: number) {
    var q = new Question(
      id,
      title,
      type,
      "17.2%",
      diff,
      slides,
      ans);
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