import { Component } from '@angular/core';
import { TeamService } from '../teamservice/team.service';
import { Team } from '../teamservice/team';
import { QuestionService } from '../questionservice/question.service';
import { Question } from '../questionservice/question';
import { MatTableModule } from '@angular/material/table';
import { MatButtonModule } from '@angular/material/button';
import {MatDialog, MatDialogModule} from '@angular/material/dialog';
import { QuestionPaneComponent } from '../questionpane/questionpane.component';
import { ActivatedRoute } from '@angular/router';
import { NgClass } from '@angular/common';

export class QuestionItem {
  id: number = 0;
  question?: Question;
  x: number = 0;
  y: number = 0;
  opened?: boolean = false;
}

const QUESTIONS_1: QuestionItem[] = [
  {id:1, x: 165, y: 90},
  {id:2, x: 435, y: 80},
  {id:3, x: 710, y: 90},

  {id:4, x: 220, y: 285},
  {id:5, x: 435, y: 300},
  {id:6, x: 665, y: 285},

  {id:7, x: 90, y: 455},
  {id:8, x: 270, y: 480},
  {id:9, x: 435, y: 540},
  {id:10, x: 610, y: 480},
  {id:11, x: 780, y: 455},
]
const QUESTIONS_2: QuestionItem[] = [
  {id:12, x: 115, y: 140},
  {id:13, x: 335, y: 90},
  {id:14, x: 550, y: 90},
  {id:16, x: 750, y: 140},

  {id:15, x: 290, y: 270},
  {id:17, x: 570, y: 270},

  {id:18, x: 120, y: 450},
  {id:19, x: 300, y: 455},
  {id:20, x: 435, y: 560},
  {id:21, x: 570, y: 455},
  {id:22, x: 750, y: 450},
]
const QUESTIONS_3: QuestionItem[] = [
  {id:23, x: 190, y: 80},
  {id:24, x: 440, y: 75},
  {id:25, x: 690, y: 80},

  {id:26, x: 80, y: 230},
  {id:27, x: 290, y: 260},
  {id:28, x: 590, y: 260},
  {id:29, x: 800, y: 230},
  
  {id:30, x: 160, y: 390},
  {id:32, x: 440, y: 390},
  {id:33, x: 720, y: 390},

  {id:31, x: 440, y: 580},
]

@Component({
  selector: 'app-groupstage',
  standalone: true,
  imports: [MatTableModule, MatButtonModule, MatDialogModule, NgClass],
  templateUrl: './groupstage.component.html',
  styleUrl: './groupstage.component.css'
})
export class GroupstageComponent {
  public teams: Team[] = [];
  public bgclass: string = "";
  displayedColumns: string[] = [
    'si', 'title', 'w', 'd', 'l', 'pts', 'gf', 'ga', 'gd'];
  public questionsGrid: QuestionItem[] = []

  constructor(
      private _route: ActivatedRoute,
      private teamService: TeamService,
      private qs : QuestionService,
      public dialog: MatDialog) {
    this.teams = teamService.getSortedTeams();
  }

  ngOnInit() {
    this._route.params.subscribe(params => {
        this.bgclass = 'group-map-bg-' + params['id'];
        switch(params['id']) {
          case '1': this.questionsGrid = QUESTIONS_1; break;
          case '2': this.questionsGrid = QUESTIONS_2; break;
          case '3': this.questionsGrid = QUESTIONS_3; break;
        }
        this.questionsGrid.forEach(qe => {
          qe.question = this.qs.getQuestion(qe.id)
        });
    });
}

  openQuestion(qi: QuestionItem) {
    if (!qi.opened) {
      qi.opened = true;
      return;
    }
    const dialogRef = this.dialog.open(
      QuestionPaneComponent,
      {data: qi.question});

    dialogRef.afterClosed().subscribe((result : any) => {
      console.log(`Dialog result: ${result}`);
    });
  }
}
