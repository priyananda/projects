import { Component } from '@angular/core';
import { CommonModule } from '@angular/common';
import { RouterOutlet, RouterLink, RouterLinkActive } from '@angular/router';
import { MatTabsModule } from '@angular/material/tabs';
import { TeampanelComponent } from './teampanel/teampanel.component';
import { Question } from './questionservice/question';
import { QuestionService } from './questionservice/question.service';
import { MatTableModule } from '@angular/material/table';
import {MatDialog, MatDialogModule} from '@angular/material/dialog';
import { QuestionPaneComponent } from './questionpane/questionpane.component';
import {MatSidenavModule} from '@angular/material/sidenav';
import {MatButtonModule} from '@angular/material/button';
import {MatInputModule} from '@angular/material/input';
import { MatIconModule } from '@angular/material/icon';


@Component({
  selector: 'app-root',
  standalone: true,
  imports: [
    CommonModule, RouterOutlet, MatDialogModule,
    MatTabsModule, TeampanelComponent, MatTableModule,
    MatSidenavModule, MatButtonModule,
    RouterLink, RouterLinkActive, MatInputModule,
    MatIconModule
  ],
  templateUrl: './app.component.html',
  styleUrl: './app.component.css',
})
export class AppComponent {
  title = 'First Quiz of 2026';
  questions: Question[];

  constructor(qs : QuestionService, public dialog: MatDialog) {
    this.questions = qs.getQuestions();
  }

  openQuestion(question: Question) {
    const dialogRef = this.dialog.open(
      QuestionPaneComponent,
      {data: question});

    dialogRef.afterClosed().subscribe((result : any) => {
      console.log(`Dialog result: ${result}`);
    });
  }
}
