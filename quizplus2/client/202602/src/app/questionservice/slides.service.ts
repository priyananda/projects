import { Injectable } from '@angular/core';
import { Question } from './question';

@Injectable({
  providedIn: 'root'
})
export class SlidesService {
  private slideImages : string[] = [
    "",
    
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-01.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-02.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-03.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-04.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-05.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-06.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-07.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-08.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-09.png",

    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-10.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-11.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-12.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-13.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-14.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-15.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-16.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-17.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-18.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-19.png",

    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-20.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-21.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-22.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-23.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-24.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-25.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-26.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-27.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-28.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-29.png",

    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-30.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-31.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-32.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-33.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-34.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-35.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-36.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-37.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-38.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-39.png",

    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-40.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-41.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-42.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-43.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-44.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-45.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-46.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-47.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-48.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-49.png",

    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-50.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-51.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-52.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-53.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-54.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-55.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-56.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-57.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-58.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-59.png",


    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-60.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-61.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-62.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-63.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-64.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-65.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-66.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-67.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-68.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-69.png",

    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-70.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-71.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-72.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-73.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-74.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-75.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-76.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-77.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-78.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-79.png",

    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-80.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-81.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-82.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202602/Slide-83.png",
  ];

  getSlideImage(id: number) {
    return this.slideImages[id];
  }
}