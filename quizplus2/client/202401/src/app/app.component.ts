import { Component } from '@angular/core';
import { CommonModule } from '@angular/common';
import { RouterOutlet } from '@angular/router';
import { MatTabsModule } from '@angular/material/tabs';
import { TeampanelComponent } from './teampanel/teampanel.component';
import { Question } from './questionservice/question';
import { QuestionService } from './questionservice/question.service';
import { MatTableModule } from '@angular/material/table';
import {MatDialog, MatDialogModule} from '@angular/material/dialog';
import { QuestionPaneComponent } from './questionpane/questionpane.component';


@Component({
  selector: 'app-root',
  standalone: true,
  imports: [
    CommonModule, RouterOutlet, MatDialogModule,
    MatTabsModule, TeampanelComponent, MatTableModule],
  templateUrl: './app.component.html',
  styleUrl: './app.component.css',
})
export class AppComponent {
  title = 'First Quiz of 2024';
  questions: Question[];
  displayedColumns: string[] = [
    'status', 'title', 'type', 'difficulty'];
  DIFFICULTY_COLOR = new Map<string, string>([
    ['Easy', 'green-text'],
    ['Medium', 'yellow-text'],
    ['Hard', 'red-text'],
  ]);

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
