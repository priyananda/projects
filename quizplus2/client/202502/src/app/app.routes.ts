import { Routes } from '@angular/router';
import { GroupstageComponent } from './groupstage/groupstage.component';
import { SemifinalComponent } from './semifinal/semifinal.component';
import { FinalComponent } from './final/final.component';

export const routes: Routes = [
    {path: 'group/:id', component: GroupstageComponent},
    {path: 'final', component: FinalComponent},
];
