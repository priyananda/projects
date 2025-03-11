import { ComponentFixture, TestBed } from '@angular/core/testing';

import { SemifinalComponent } from './semifinal.component';

describe('SemifinalComponent', () => {
  let component: SemifinalComponent;
  let fixture: ComponentFixture<SemifinalComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [SemifinalComponent]
    })
    .compileComponents();
    
    fixture = TestBed.createComponent(SemifinalComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
