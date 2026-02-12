import { Injectable } from '@angular/core';
import { Team } from './team';

@Injectable({
  providedIn: 'root'
})
export class TeamService {
  private teams: Team[] = [];
  private sorted: Team[] = [];
  private static readonly TEAM_NAMES: string[] = [
    "Paris St Germain",
    "FC Barcelona",
    "Real Madrid",
    "Bayern Munich",
    "Manchester City",
    "Liverpool"
  ];

  constructor() {
    for (var i = 0; i < TeamService.TEAM_NAMES.length; ++i) {
      var t = new Team(i + 1, TeamService.TEAM_NAMES[i]);
      t.load();
      this.teams.push(t);
      this.sorted.push(t);
    }
  }

  getTeams() {
    return this.teams;
  }

  sortTeams() {
    this.sorted.sort((a, b) => a.getScore().compareTo(b.getScore()))
  }

  getSortedTeams() {
    return this.sorted;
  }

  getTeam(id: number) {
    return this.teams[id - 1];
  }
}