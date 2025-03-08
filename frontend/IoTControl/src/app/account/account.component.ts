import { HttpClient } from '@angular/common/http';
import { Component, OnInit } from '@angular/core';
import { CommonModule } from '@angular/common'; // ✅ Import CommonModule

@Component({
  selector: 'app-account',
  standalone: true, // ✅ Required in Angular 17+ for independent components
  imports: [CommonModule], // ✅ Add CommonModule to enable *ngFor
  templateUrl: './account.component.html',
  styleUrls: ['./account.component.css']
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