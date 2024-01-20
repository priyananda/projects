import { Injectable } from '@angular/core';
import { Question } from './question';

@Injectable({
  providedIn: 'root'
})
export class SlidesService {
  private slideImages : string[] = [
    "",
    "http://lh3.googleusercontent.com/GQauCAlaaKP_gKktbZndXlbySJ2dfQq2kSgqF_pyB5JKdMrMFux1SRaZKuD2AMiu_n_NlTFHnnYrL8qBgqY0SVe2yjs",
	  "http://lh3.googleusercontent.com/VGr_002ynkyLMUi9g2wZBx3hB4o9KuEurwpUwLOqXupWn4CTlC5NNdm792NxtwTbYcAaQ-nLRGZn8E_7hVgvNaj19Q",
	  "http://lh3.googleusercontent.com/hvZhsNMZVkiNQWnWUzlVn1xtez-j428CarF-OPOhgHqmDw9SLQW__mGwMD0kl0q9LKcnk7-gFW262EdTWSsg1WrJ",
	  "http://lh3.googleusercontent.com/hDIQ2n5rZ3n-ACWqrKe36rwe_xoah1AJFFi_2vga9pwnl9L0AFT_K-zi_a9GKqBWJL69yCavOv527wTDYrCUrOVfXug",
	  "http://lh3.googleusercontent.com/9jyl5VMsvSdtq9PkiCsg10YBuKbJGuXoM366yqKYZGkWQEQPgkU9BERu4XTuFAJnC5aAOXZB9kWt73Tg-IoePqul8dI",
	  "http://lh3.googleusercontent.com/ePaMGgCz3HApIrS_5j6Tgu_6rLs42WYdRyckrQSSdhhwOsM2j6hhzI50-gpxQD9aB7Htw_d7ogfA4smd30Oj1RTush4",
    "http://lh3.googleusercontent.com/qb7tbpBQ5QOA3AQNHqcsYofgVfN2zlo5qa6yg-fVLi8IFv8iFtgfh89pzk_W13NxVCqmpzrzaEuGlFP2eR9xn6fDYg"
  ];

  getSlideImage(id: number) {
    return this.slideImages[id];
  }
}