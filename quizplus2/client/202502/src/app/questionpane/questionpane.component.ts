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
import {DomSanitizer, SafeUrl} from '@angular/platform-browser';

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
  videoUrl: SafeUrl = "";

  constructor(@Inject(MAT_DIALOG_DATA) public question: Question, private sanitizer: DomSanitizer) {
    this.contentImages = question.getContentImageUrls();
    this.answerImage = question.getAnswerImageUrl();
    this.setCurrentImage();
  }

  setCurrentImage() {
    var video = "";
    if (this.currentIndex < 0){
      this.currentImage = this.answerImage;
      video = this.question.getAnswerVideo();
    } else {
      this.currentImage = this.contentImages[this.currentIndex];
      video = this.question.getContentVideo();
    }
    if (video !== "") {
      this.videoUrl = this.sanitizer.bypassSecurityTrustResourceUrl("https://www.youtube.com/embed/" + video);
    }
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
