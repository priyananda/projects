import { Component } from '@angular/core';
import { Router } from '@angular/router';
import { QuizService, Round, Team } from '../services/quiz';

@Component({
  selector: 'app-home',
  standalone: false,
  templateUrl: './home.html',
  styleUrl: './home.scss',
})
export class Home {
  rounds: Round[];
  teams: Team[];
  editingTeam: number | null = null;
  editValue = '';

  constructor(public quizService: QuizService, private router: Router) {
    this.rounds = quizService.rounds;
    this.teams = quizService.getTeams();
    quizService.teams$.subscribe(t => this.teams = t);
  }

  startRound(round: Round) {
    this.quizService.setCurrentRound(round.id);
    this.router.navigate(['/round', round.id]);
  }

  startEdit(team: Team) {
    this.editingTeam = team.id;
    this.editValue = team.name;
  }

  saveEdit(teamId: number) {
    if (this.editValue.trim()) {
      this.quizService.updateTeamName(teamId, this.editValue.trim());
    }
    this.editingTeam = null;
  }

  resetAll() {
    this.quizService.resetScores();
  }
}
