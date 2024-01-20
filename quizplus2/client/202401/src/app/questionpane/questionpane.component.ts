import { Component, Inject } from '@angular/core';
import { Question } from '../questionservice/question';
import {
  MAT_DIALOG_DATA,
  MatDialogTitle,
  MatDialogContent,
  MatDialogModule,
} from '@angular/material/dialog';
import { MatButtonModule } from '@angular/material/button';
import {MatIconModule} from '@angular/material/icon';

@Component({
  selector: 'app-questionpane',
  standalone: true,
  imports: [MatDialogTitle, MatDialogContent,
    MatDialogModule, MatButtonModule, MatIconModule],
  templateUrl: './questionpane.component.html',
  styleUrl: './questionpane.component.css'
})
export class QuestionPaneComponent {
  contentImages : string[] = [];
  answerImage : string = "";
  currentIndex: number = 0;
  currentImage: string = "";

  constructor(@Inject(MAT_DIALOG_DATA) public question: Question) {
    this.contentImages = question.getContentImageUrls();
    this.answerImage = question.getAnswerImageUrl();
    this.setCurrentImage();
  }

  setCurrentImage() {
    if (this.currentIndex < 0)
      this.currentImage = this.answerImage;
    else
      this.currentImage = this.contentImages[this.currentIndex];
  }

  nextImage() {
    if (this.currentIndex < 0)
      return;
    if (this.currentIndex < this.contentImages.length - 1)
      this.currentIndex += 1;
    this.setCurrentImage();
  }

  prevImage() {
    if (this.currentIndex < 0)
      return;
    if (this.currentIndex > 0)
      this.currentIndex -= 1;
    this.setCurrentImage();
  }

  showAnswer() {
    this.currentIndex = -1;
    this.question.answer();
    this.setCurrentImage();
  }
}
