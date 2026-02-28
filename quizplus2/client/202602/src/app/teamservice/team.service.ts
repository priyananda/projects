import { Injectable } from '@angular/core';
import { Team } from './team';

@Injectable({
  providedIn: 'root'
})
export class TeamService {
  private teams: Team[] = [];
  private sorted: Team[] = [];

  constructor() {
    for (var i = 0; i < 5; ++i) {
      var t = new Team(i + 1);
      t.load();
      this.teams.push(t);
      this.sorted.push(t);
    }
  }

  getTeams() {
    return this.teams;
  }

  getTeam(id: number) {
    return this.teams[id - 1];
  }
}