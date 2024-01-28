import { Injectable } from '@angular/core';
import { Question } from './question';

@Injectable({
  providedIn: 'root'
})
export class SlidesService {
  private slideImages : string[] = [
    "",

    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide001.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide002.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide003.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide004.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide005.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide006.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide007.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide008.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide009.png",

    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide010.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide011.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide012.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide013.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide014.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide015.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide016.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide017.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide018.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide019.png",

    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide020.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide021.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide022.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide023.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide024.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide025.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide026.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide027.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide028.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide029.png",

    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide030.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide031.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide032.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide033.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide034.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide035.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide036.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide037.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide038.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide039.png",

    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide040.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide041.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide042.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide043.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide044.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide045.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide046.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide047.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide048.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide049.png",

    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide050.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide051.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide052.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide053.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide054.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide055.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide056.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide057.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide058.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide059.png",


    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide060.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide061.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide062.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide063.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide064.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide065.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide066.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide067.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide068.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide069.png",


    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide070.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide071.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide072.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide073.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide074.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide075.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide076.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide077.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide078.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide079.png",


    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide080.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide081.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide082.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide083.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide084.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide085.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide086.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide087.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide088.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide089.png",


    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide090.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide091.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide092.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide093.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide094.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide095.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide096.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide097.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide098.png",
    "https://storage.googleapis.com/quizplus_storage/quiz202401/Slide099.png",
  ];

  getSlideImage(id: number) {
    return this.slideImages[id];
  }
}