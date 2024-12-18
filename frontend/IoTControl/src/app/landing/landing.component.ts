import { Component } from '@angular/core';
import { BottomBarComponent } from "./bottom-bar/bottom-bar.component";
import { BodyComponent } from "./body/body.component";
import { TopBarComponent } from "./top-bar/top-bar.component";

@Component({
  selector: 'app-landing',
  imports: [BottomBarComponent, BodyComponent, TopBarComponent],
  templateUrl: './landing.component.html',
  styleUrl: './landing.component.css'
})
export class LandingComponent {

}
