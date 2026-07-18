import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { Home } from './home/home';
import { Quiz } from './quiz/quiz';
import { Scoreboard } from './scoreboard/scoreboard';

const routes: Routes = [
  { path: '', component: Home },
  { path: 'round/:id', component: Quiz },
  { path: 'scoreboard', component: Scoreboard },
  { path: '**', redirectTo: '' }
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
