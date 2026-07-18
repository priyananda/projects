import { Injectable } from '@angular/core';
import { BehaviorSubject } from 'rxjs';

export interface Team {
  id: number;
  name: string;
  icon: string;
  score: number;
  color: string;
}

export interface Round {
  id: number;
  name: string;
  subTitle: string;
  theme: string;
  icon: string;
  description: string;
  questionCount: number;
  pointsPerQuestion: number;
  color: string;
}

@Injectable({
  providedIn: 'root'
})
export class QuizService {
  private teamsSubject = new BehaviorSubject<Team[]>(this.initTeams());
  teams$ = this.teamsSubject.asObservable();

  private currentRoundSubject = new BehaviorSubject<number | null>(null);
  currentRound$ = this.currentRoundSubject.asObservable();

  private currentQuestionSubject = new BehaviorSubject<number>(1);
  currentQuestion$ = this.currentQuestionSubject.asObservable();

  rounds: Round[] = [
    {
      id: 1,
      name: 'Itihaas',
      subTitle: 'इतिहास',
      theme: 'History & Heritage',
      icon: '🏛️',
      description: 'Delve into the rich tapestry of Indian history — from ancient empires to the freedom struggle',
      questionCount: 10,
      pointsPerQuestion: 10,
      color: '#C0392B'
    },
    {
      id: 2,
      name: 'Vijnana',
      subTitle: 'विज्ञान',
      theme: 'Science & Discovery',
      icon: '🔬',
      description: 'Explore the wonders of science — from ancient Indian mathematics to modern breakthroughs',
      questionCount: 10,
      pointsPerQuestion: 10,
      color: '#1A5276'
    },
    {
      id: 3,
      name: 'Kala',
      subTitle: 'कला',
      theme: 'Arts & Culture',
      icon: '🎭',
      description: 'Celebrate the vibrant arts — classical dance, music, literature, and cinema of India',
      questionCount: 10,
      pointsPerQuestion: 10,
      color: '#7D3C98'
    },
    {
      id: 4,
      name: 'Krida',
      subTitle: 'क्रीड़ा',
      theme: 'Sports & Champions',
      icon: '🏆',
      description: 'Test your knowledge of Indian sporting legends — cricket, hockey, chess, and beyond',
      questionCount: 10,
      pointsPerQuestion: 10,
      color: '#1E8449'
    },
    {
      id: 5,
      name: 'Vishva',
      subTitle: 'विश्व',
      theme: 'World Knowledge',
      icon: '🌍',
      description: 'A journey around the globe — geography, world events, and global cultures',
      questionCount: 10,
      pointsPerQuestion: 10,
      color: '#D35400'
    }
  ];

  private initTeams(): Team[] {
    return [
      { id: 1, name: 'Agni',    icon: '🔥', score: 0, color: '#E74C3C' },
      { id: 2, name: 'Vayu',    icon: '💨', score: 0, color: '#3498DB' },
      { id: 3, name: 'Jal',     icon: '💧', score: 0, color: '#1ABC9C' },
      { id: 4, name: 'Prithvi', icon: '🌿', score: 0, color: '#2ECC71' },
      { id: 5, name: 'Akash',   icon: '⚡', score: 0, color: '#9B59B6' },
      { id: 6, name: 'Surya',   icon: '☀️', score: 0, color: '#F39C12' }
    ];
  }

  getTeams(): Team[] {
    return this.teamsSubject.getValue();
  }

  getRound(id: number): Round | undefined {
    return this.rounds.find(r => r.id === id);
  }

  setCurrentRound(id: number | null) {
    this.currentRoundSubject.next(id);
    this.currentQuestionSubject.next(1);
  }

  addScore(teamId: number, points: number) {
    const teams = this.teamsSubject.getValue().map(t =>
      t.id === teamId ? { ...t, score: Math.max(0, t.score + points) } : t
    );
    this.teamsSubject.next(teams);
  }

  nextQuestion() {
    const current = this.currentQuestionSubject.getValue();
    const round = this.rounds.find(r => r.id === this.currentRoundSubject.getValue());
    if (round && current < round.questionCount) {
      this.currentQuestionSubject.next(current + 1);
    }
  }

  prevQuestion() {
    const current = this.currentQuestionSubject.getValue();
    if (current > 1) {
      this.currentQuestionSubject.next(current - 1);
    }
  }

  resetScores() {
    this.teamsSubject.next(this.initTeams());
  }

  getSortedTeams(): Team[] {
    return [...this.teamsSubject.getValue()].sort((a, b) => b.score - a.score);
  }

  updateTeamName(teamId: number, name: string) {
    const teams = this.teamsSubject.getValue().map(t =>
      t.id === teamId ? { ...t, name } : t
    );
    this.teamsSubject.next(teams);
  }

  jumpToQuestion(n: number) {
    const round = this.rounds.find(r => r.id === this.currentRoundSubject.getValue());
    if (round && n >= 1 && n <= round.questionCount) {
      this.currentQuestionSubject.next(n);
    }
  }
}
