import { Component, Input, OnInit } from '@angular/core';
import { TeamService } from '../teamservice/team.service';
import { Team } from '../teamservice/team';
import {MatCardModule} from '@angular/material/card';
import {MatIconModule} from '@angular/material/icon';
import {MatButtonModule} from '@angular/material/button';

@Component({
  selector: 'teampanel',
  imports: [MatCardModule, MatIconModule, MatButtonModule],
  templateUrl: './teampanel.component.html',
  styleUrl: './teampanel.component.css',
  standalone: true
})
export class TeampanelComponent implements OnInit{
  @Input() teamId: number = 0;
  team: Team = new Team(0);

  constructor(private teamService: TeamService) {
  }

  ngOnInit() {
    this.team = this.teamService.getTeam(this.teamId);
  }
}
