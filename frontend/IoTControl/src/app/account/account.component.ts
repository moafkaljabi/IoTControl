import { HttpClient } from '@angular/common/http';
import { Component, OnInit } from '@angular/core';
import { CommonModule } from '@angular/common';  // Ensure CommonModule is imported for *ngFor functionality

@Component({
  selector: 'app-account',
  standalone: true,  // This is required for Angular 17+ standalone components
  imports: [CommonModule],  // Import CommonModule for *ngFor functionality
  templateUrl: './account.component.html',
  styleUrls: ['./account.component.css']
})
export class AccountComponent implements OnInit {
  accounts: any[] = [];

  constructor(private http: HttpClient) {}

  ngOnInit() {
    this.getAccounts();  // Call the API to fetch account data
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
