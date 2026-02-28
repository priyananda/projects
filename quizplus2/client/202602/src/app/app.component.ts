import { Component, OnInit } from '@angular/core';
import { CommonModule } from '@angular/common';
import { RouterOutlet, RouterLink, RouterLinkActive } from '@angular/router';
import { MatTabsModule } from '@angular/material/tabs';
import { MatTableModule } from '@angular/material/table';
import {MatDialog, MatDialogModule} from '@angular/material/dialog';
import {MatSidenavModule} from '@angular/material/sidenav';
import {MatButtonModule} from '@angular/material/button';
import {MatInputModule} from '@angular/material/input';
import { MatIconModule } from '@angular/material/icon';
import { MathJaxParagraphComponent } from './math-jax-paragraph/math-jax-paragraph.js';
import {MatGridListModule} from '@angular/material/grid-list';
import { Question } from './questionservice/question.js';
import { QuestionPaneComponent } from './questionpane/questionpane.component.js';
import { QuestionService } from './questionservice/question.service.js';

@Component({
  selector: 'app-root',
  standalone: true,
  imports: [
    CommonModule, RouterOutlet, MatDialogModule,
    MatTabsModule, MatTableModule,
    MatSidenavModule, MatButtonModule,
    RouterLink, RouterLinkActive, MatInputModule,
    MatIconModule, MathJaxParagraphComponent,
    MatGridListModule
  ],
  templateUrl: './app.component.html',
  styleUrl: './app.component.css',
})
export class AppComponent implements OnInit {
  title = 'First Quiz of 2026';
  inpEmbedding = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0];
  outEmbedding = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0];
  public inpEmbS = "";
  public outEmbS = "";
  questions: Question[];

  constructor(qs : QuestionService, public dialog: MatDialog) {
    this.questions = qs.getQuestions();
  }

  ngOnInit() {
    this.setEmbStrings();
  }

  setEmbStrings() {
    var newInpEmbS = "$$embedding = \\begin{bmatrix}6.7"
    var newOutEmbS = "$$embedding = \\begin{bmatrix}4.2"
    for (var i = 0; i < 10; ++i) {
      newInpEmbS += "," + this.inpEmbedding[i].toFixed(2);
      newOutEmbS += "," + this.outEmbedding[i].toFixed(2);
    }
    newInpEmbS += "\\end{bmatrix}$$";
    newOutEmbS += "\\end{bmatrix}$$";
    this.inpEmbS = newInpEmbS;
    this.outEmbS = newOutEmbS;
  }

  onInputChange() {
    for (var i = 0; i < 10; ++i) {
      this.inpEmbedding[i] = Math.random();
    }
    this.setEmbStrings();
  }

  openQuestion(id: number) {
    var question = this.questions[id - 1];
    const dialogRef = this.dialog.open(
      QuestionPaneComponent,
      {data: question});

    dialogRef.afterClosed().subscribe((result : any) => {
      console.log(`Dialog result: ${result}`);
    });
  }
}
