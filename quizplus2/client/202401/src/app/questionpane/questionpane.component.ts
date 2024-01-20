import { Component, Inject } from '@angular/core';
import { Question } from '../questionservice/question';
import {
  MAT_DIALOG_DATA,
  MatDialogTitle,
  MatDialogContent,
} from '@angular/material/dialog';

@Component({
  selector: 'app-questionpane',
  standalone: true,
  imports: [MatDialogTitle, MatDialogContent],
  templateUrl: './questionpane.component.html',
  styleUrl: './questionpane.component.css'
})
export class QuestionPaneComponent {
  constructor(@Inject(MAT_DIALOG_DATA) public question: Question) {}
}
