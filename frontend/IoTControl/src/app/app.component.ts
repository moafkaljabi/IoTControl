import { Component } from '@angular/core';
import { RouterOutlet } from '@angular/router';
import { AccountComponent } from './account/account.component'; // ✅ Import the standalone component

@Component({
  selector: 'app-root',
  standalone: true, // ✅ Mark AppComponent as standalone
  imports: [RouterOutlet, AccountComponent], // ✅ Use AccountComponent
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {}
