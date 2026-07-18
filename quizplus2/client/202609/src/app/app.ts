import { Component } from '@angular/core';
import { Router, NavigationEnd } from '@angular/router';
import { QuizService } from './services/quiz';
import { filter } from 'rxjs/operators';

@Component({
  selector: 'app-root',
  templateUrl: './app.html',
  standalone: false,
  styleUrl: './app.scss'
})
export class App {
  showNav = false;

  constructor(public quizService: QuizService, private router: Router) {
    this.router.events.pipe(
      filter(e => e instanceof NavigationEnd)
    ).subscribe((e: any) => {
      this.showNav = e.url !== '/';
    });
  }

  goHome() {
    this.router.navigate(['/']);
  }

  goScoreboard() {
    this.router.navigate(['/scoreboard']);
  }
}
