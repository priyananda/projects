import { Component } from '@angular/core';
import { TeamService } from '../teamservice/team.service.js';
import { Team } from '../teamservice/team';
import { QuestionService } from '../questionservice/question.service.js';
import { Question } from '../questionservice/question';
import { MatTableModule } from '@angular/material/table';
import { MatButtonModule } from '@angular/material/button';
import {MatDialog, MatDialogModule} from '@angular/material/dialog';
import { QuestionPaneComponent } from '../questionpane/questionpane.component';
import { ActivatedRoute, RouterLink } from '@angular/router';
import { NgClass } from '@angular/common';
import { MatCard, MatCardModule } from '@angular/material/card';
import { MathJaxParagraphComponent } from '../math-jax-paragraph/math-jax-paragraph.js';
import { MatIconModule } from '@angular/material/icon';

const QMATRIX_1 = [
  [5, 0, 0, 6, 0],
  [0, 8, 0, 0, 7],
  [0, 9, 10, 0, 0],
  [11, 0, 0, 12, 0],
  [0, 13, 14, 0, 0],
];

const QMATRIX_2 = [
  [0, 15, 0, 0, 16],
  [17, 0, 0, 18, 0],
  [19, 0, 0, 20, 0],
  [0, 21, 22, 0, 0],
  [0, 0, 24, 0, 23],
];

const QMATRIX_3 = [
  [25, 0, 0, 26, 0],
  [0, 28, 0, 0, 27],
  [0, 29, 30, 0, 0],
  [31, 0, 0, 32, 0],
  [0, 0, 34, 0, 33],
];

const QMATRIX_4 = [
  [0, 35, 0, 0, 36],
  [37, 0, 0, 38, 0],
  [39, 0, 0, 40, 0],
  [0, 41, 42,0, 0],
  [0, 0, 44, 0, 43],
];

@Component({
  selector: 'app-groupstage',
  standalone: true,
  imports: [MatTableModule, MatButtonModule, MatDialogModule,
    NgClass, MatCardModule, MathJaxParagraphComponent,
    MatIconModule, RouterLink
  ],
  templateUrl: './groupstage.component.html',
  styleUrl: './groupstage.component.css'
})
export class GroupstageComponent {
  public teams: string[] = [];
  public qmatrix = QMATRIX_1;
  opened = new Set();

  constructor(
      private _route: ActivatedRoute,
      private teamService: TeamService,
      private qs : QuestionService,
      public dialog: MatDialog) {
    var i = 1;
    for (var team of teamService.getTeams()) {
      this.teams.push("$$t_" + team.getId() + " = " + team.getScore().toFixed(2) + "$$");
    }
  }

  ngOnInit() {
    this._route.params.subscribe(params => {
        switch(params['id']) {
          case '1': this.qmatrix = QMATRIX_1; break;
          case '2': this.qmatrix = QMATRIX_2; break;
          case '3': this.qmatrix = QMATRIX_3; break;
          case '4': this.qmatrix = QMATRIX_4; break;
        }
    });
  }

  openQuestion(qid: number | undefined) {
    if (qid === undefined)
      return;
    const dialogRef = this.dialog.open(
      QuestionPaneComponent,
      {data: this.qs.getQuestion(qid)});

    dialogRef.afterClosed().subscribe((result : any) => {
      console.log(`Dialog result: ${result}`);
    });
  }
}
