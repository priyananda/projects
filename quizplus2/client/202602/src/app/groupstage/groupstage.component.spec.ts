import { ComponentFixture, TestBed } from '@angular/core/testing';

import { GroupstageComponent } from './groupstage.component';

describe('GroupstageComponent', () => {
  let component: GroupstageComponent;
  let fixture: ComponentFixture<GroupstageComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [GroupstageComponent]
    })
    .compileComponents();
    
    fixture = TestBed.createComponent(GroupstageComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
