import { ComponentFixture, TestBed } from '@angular/core/testing';

import { QuestionpaneComponent } from './questionpane.component';

describe('QuestionpaneComponent', () => {
  let component: QuestionpaneComponent;
  let fixture: ComponentFixture<QuestionpaneComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [QuestionpaneComponent]
    })
    .compileComponents();
    
    fixture = TestBed.createComponent(QuestionpaneComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
