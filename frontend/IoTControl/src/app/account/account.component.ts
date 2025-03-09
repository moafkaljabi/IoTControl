import { HttpClient } from '@angular/common/http';
import { Component, OnInit } from '@angular/core';
import { CommonModule } from '@angular/common'; // Needed for *ngFor

@Component({
  selector: 'app-account',
  templateUrl: './account.component.html',
  styleUrls: ['./account.component.css'],
  standalone: true, 
  imports: [CommonModule] // Necessary for *ngFor
})
export class AccountComponent implements OnInit {
  accounts: any[] = [];

  constructor(private http: HttpClient) {}

  ngOnInit() {
    this.getAccounts();
  }

  getAccounts() {
    this.http.get<any[]>('http://localhost:3000/Account')
      .subscribe({
        next: (data) => {
          console.log('Accounts:', data);
          this.accounts = data;
        },
        error: (err) => {
          console.error('API request failed:', err);
        }
      });
  }
  
  testClick() {
    alert('Button clicked!');
  }
}
