import { Component, OnInit } from '@angular/core';
import { MatDialog, MatDialogModule } from '@angular/material/dialog';
import { MatGridListModule } from '@angular/material/grid-list';
import { ActivatedRoute, Route, RouterLink } from '@angular/router';
import { Question } from '../questionservice/question.js';
import { QuestionService } from '../questionservice/question.service.js';
import { QuestionPaneComponent } from '../questionpane/questionpane.component.js';
import { MatCardModule } from '@angular/material/card';
import { MatButtonModule } from '@angular/material/button';

@Component({
  selector: 'app-semifinal',
  standalone: true,
  imports: [MatDialogModule, MatGridListModule, RouterLink, MatCardModule, MatButtonModule],
  templateUrl: './semifinal.component.html',
  styleUrl: './semifinal.component.css'
})
export class SemifinalComponent implements OnInit {
  showQuestions = false;
  showFirstButton = true;
  questions: Question[];

  constructor(qs: QuestionService, public dialog: MatDialog, private _route: ActivatedRoute) {
    this.questions = qs.getQuestions();
  }

  openQuestion(id: number) {
    var question = this.questions[id - 1];
    const dialogRef = this.dialog.open(
      QuestionPaneComponent,
      { data: question });

    dialogRef.afterClosed().subscribe((result: any) => {
      console.log(`Dialog result: ${result}`);
    });
  }

  ngOnInit() {
    this._route.queryParams.subscribe(params => {
      if (params['sq']) {
        this.showQuestions = true;
      }
    });
  }
}
