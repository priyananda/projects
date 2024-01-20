import { Injectable } from '@angular/core';
import { Team } from './team';

@Injectable({
  providedIn: 'root'
})
export class TeamService {
  private static NUM_TEAMS : number = 6;
  private teams: Team[] = [];

  constructor() {
    for (var i = 0; i < TeamService.NUM_TEAMS; ++i) {
      var t = new Team(i + 1);
      t.load();
      this.teams.push(t);
    }
  }

  getTeams() {
    return this.teams;
  }

  getTeam(id: number) {
    return this.teams[id - 1];
  }
}