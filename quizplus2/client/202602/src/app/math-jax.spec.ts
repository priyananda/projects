import { TestBed } from '@angular/core/testing';

import { MathJax } from './math-jax';

describe('MathJax', () => {
  let service: MathJax;

  beforeEach(() => {
    TestBed.configureTestingModule({});
    service = TestBed.inject(MathJax);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
});
