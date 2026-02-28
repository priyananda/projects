import { Component, ElementRef, Input, OnChanges, ViewChild } from '@angular/core';
import { MathJaxService } from '../math-jax.js';

@Component({
  selector: 'app-math-jax-paragraph',
  standalone: true,
  imports: [],
  templateUrl: './math-jax-paragraph.html',
  styleUrl: './math-jax-paragraph.css'
})
export class MathJaxParagraphComponent implements OnChanges {
  @ViewChild('mathParagraph') paragraphElement: any;
  @Input({ required: true }) mathString!: string;

  constructor(private mathJaxService: MathJaxService) {}

  ngOnInit() {
    this.mathJaxService.getMathJaxLoadedPromise().then(() => {
      console.log('MathJax loaded, rendering math');
      
      // Insert the input string
      this.paragraphElement.nativeElement.innerHTML = this.mathString;
      
      // Render the Latex
      this.mathJaxService.render();
    });
  }

  ngOnChanges() {
    this.mathJaxService.getMathJaxLoadedPromise().then(() => {
      console.log('MathJax loaded, rendering math');
      
      // Insert the input string
      this.paragraphElement.nativeElement.innerHTML = this.mathString;
      
      // Render the Latex
      this.mathJaxService.render();
    });
  }
}