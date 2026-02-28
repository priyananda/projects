import { Routes } from '@angular/router';
import { GroupstageComponent } from './groupstage/groupstage.component.js';
import { SemifinalComponent } from './semifinal/semifinal.component.js';

export const routes: Routes = [
    {path: '', component: SemifinalComponent},
    {path: 'r/:id', component: GroupstageComponent},
];
