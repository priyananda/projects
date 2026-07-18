import { Component } from '@angular/core';
import { Router } from '@angular/router';
import { QuizService, Team, Round } from '../services/quiz';

@Component({
  selector: 'app-scoreboard',
  standalone: false,
  templateUrl: './scoreboard.html',
  styleUrl: './scoreboard.scss',
})
export class Scoreboard {
  teams: Team[] = [];
  rounds: Round[];

  constructor(public quizService: QuizService, private router: Router) {
    this.rounds = quizService.rounds;
    quizService.teams$.subscribe(t => {
      this.teams = [...t].sort((a, b) => b.score - a.score);
    });
  }

  get leader(): Team | null {
    return this.teams[0] ?? null;
  }

  getMedal(index: number): string {
    return ['🥇', '🥈', '🥉'][index] ?? '🎖️';
  }

  getBarWidth(score: number): number {
    const max = this.teams[0]?.score || 1;
    return max === 0 ? 0 : Math.max(4, (score / max) * 100);
  }

  getRankSuffix(i: number): string {
    const n = i + 1;
    if (n === 1) return 'st';
    if (n === 2) return 'nd';
    if (n === 3) return 'rd';
    return 'th';
  }

  goRound(id: number) {
    this.router.navigate(['/round', id]);
  }

  goHome() {
    this.router.navigate(['/']);
  }
}
