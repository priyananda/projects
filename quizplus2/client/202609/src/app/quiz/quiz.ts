import { Component, OnInit, OnDestroy } from '@angular/core';
import { ActivatedRoute, Router } from '@angular/router';
import { QuizService, Round, Team } from '../services/quiz';
import { Subscription } from 'rxjs';

@Component({
  selector: 'app-quiz',
  standalone: false,
  templateUrl: './quiz.html',
  styleUrl: './quiz.scss',
})
export class Quiz implements OnInit, OnDestroy {
  round: Round | null = null;
  teams: Team[] = [];
  currentQuestion = 1;
  scoringTeamId: number | null = null;
  pointsToAward = 10;
  lastAward: { teamName: string; points: number } | null = null;
  showLastAward = false;
  private subs = new Subscription();

  constructor(
    public quizService: QuizService,
    private route: ActivatedRoute,
    private router: Router
  ) {}

  ngOnInit() {
    this.subs.add(
      this.route.params.subscribe(params => {
        const id = +params['id'];
        this.round = this.quizService.getRound(id) || null;
        if (!this.round) this.router.navigate(['/']);
        this.quizService.setCurrentRound(id);
      })
    );
    this.subs.add(
      this.quizService.teams$.subscribe(t => this.teams = t)
    );
    this.subs.add(
      this.quizService.currentQuestion$.subscribe(q => this.currentQuestion = q)
    );
  }

  ngOnDestroy() {
    this.subs.unsubscribe();
  }

  get sortedTeams(): Team[] {
    return this.quizService.getSortedTeams();
  }

  get questionRange(): number[] {
    return Array.from({ length: this.round?.questionCount ?? 0 }, (_, i) => i + 1);
  }

  selectQuestion(n: number) {
    this.quizService.jumpToQuestion(n);
  }

  awardPoints(team: Team, points: number) {
    this.quizService.addScore(team.id, points);
    this.lastAward = { teamName: team.name, points };
    this.showLastAward = true;
    setTimeout(() => this.showLastAward = false, 2000);
  }

  deductPoints(team: Team, points: number) {
    this.quizService.addScore(team.id, -points);
    this.lastAward = { teamName: team.name, points: -points };
    this.showLastAward = true;
    setTimeout(() => this.showLastAward = false, 2000);
  }

  nextQuestion() {
    this.quizService.nextQuestion();
  }

  prevQuestion() {
    this.quizService.prevQuestion();
  }

  get isLastQuestion(): boolean {
    return this.currentQuestion === (this.round?.questionCount ?? 0);
  }

  get progress(): number {
    return this.round ? (this.currentQuestion / this.round.questionCount) * 100 : 0;
  }

  goScoreboard() {
    this.router.navigate(['/scoreboard']);
  }

  getMedal(index: number): string {
    return ['🥇','🥈','🥉'][index] ?? '';
  }
}
