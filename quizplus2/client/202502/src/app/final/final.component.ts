import { Component } from '@angular/core';
import { TeamService } from '../teamservice/team.service';
import { Team } from '../teamservice/team';

export class ButtonItem {
  isLeft: boolean = true;
  x: number = 0;
  y: number = 0;
  state: string = '';  

  public static readonly NONE = '';
  public static readonly GOAL = '\u{26BD}';
  public static readonly MISS = '\u{274C}';
}

@Component({
  selector: 'app-final',
  standalone: true,
  imports: [],
  templateUrl: './final.component.html',
  styleUrl: './final.component.css'
})
export class FinalComponent {
  public teams: Team[] = [];
  public leftLogo: string = "assets/team1.png";
  public rightLogo: string = "assets/team2.png";
  public leftScore: number = 0;
  public rightScore: number = 0;
  public buttons: ButtonItem[] = [
    {isLeft: true, x : 140, y : 565, state: ''},
    {isLeft: true, x : 185, y : 565, state: ''},
    {isLeft: true, x : 230, y : 565, state: ''},
    {isLeft: true, x : 278, y : 565, state: ''},
    {isLeft: true, x : 325, y : 565, state: ''},

    {isLeft: false, x : 585, y : 565, state: ''},
    {isLeft: false, x : 630, y : 565, state: ''},
    {isLeft: false, x : 675, y : 565, state: ''},
    {isLeft: false, x : 723, y : 565, state: ''},
    {isLeft: false, x : 768, y : 565, state: ''},
  ]

  constructor(private teamService: TeamService) {
    teamService.sortTeams();
    this.teams = teamService.getSortedTeams();

    this.leftLogo = this.teams[0].getIcon();
    this.rightLogo = this.teams[1].getIcon();
  }

  changeState(bi: ButtonItem) {
    switch(bi.state) {
      case '': bi.state = ButtonItem.GOAL; break;
      case ButtonItem.GOAL: bi.state = ButtonItem.MISS; break;
      case ButtonItem.MISS: bi.state = ''; break;
    }

    this.leftScore = 0;
    this.rightScore = 0;
    this.buttons.forEach(bi => {
      if (bi.state == ButtonItem.GOAL)
        if (bi.isLeft) ++this.leftScore; else ++this.rightScore;
    })
  }
}
