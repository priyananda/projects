import { Injectable } from '@angular/core';
import { Question } from './question';

@Injectable({
  providedIn: 'root'
})
export class SlidesService {
  private slideImages : string[] = [
    "",
    
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide00.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide01.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide02.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide03.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide04.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide05.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide06.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide07.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide08.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide09.png",

    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide10.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide11.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide12.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide13.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide14.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide15.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide16.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide17.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide18.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide19.png",

    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide20.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide21.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide22.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide23.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide24.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide25.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide26.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide27.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide28.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide29.png",

    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide30.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide31.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide32.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide33.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide34.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide35.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide36.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide37.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide38.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide39.png",

    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide40.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide41.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide42.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide43.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide44.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide45.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide46.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide47.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide48.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide49.png",

    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide50.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide51.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide52.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide53.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide54.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide55.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide56.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide57.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide58.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide59.png",


    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide60.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide61.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide62.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide63.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide64.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide65.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide66.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide67.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide68.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide69.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202502/Slide70.png",
  ];

  getSlideImage(id: number) {
    return this.slideImages[id];
  }
}