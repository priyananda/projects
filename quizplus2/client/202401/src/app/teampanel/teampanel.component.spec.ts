import { ComponentFixture, TestBed } from '@angular/core/testing';

import { TeampanelComponent } from './teampanel.component';

describe('TeampanelComponent', () => {
  let component: TeampanelComponent;
  let fixture: ComponentFixture<TeampanelComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [TeampanelComponent]
    })
    .compileComponents();
    
    fixture = TestBed.createComponent(TeampanelComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
