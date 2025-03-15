import { Component } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { CommonModule } from '@angular/common';

@Component({
  selector: 'app-dashboard',
  standalone: true,
  imports: [CommonModule],
  templateUrl: './dashboard.component.html',
})
export class DashboardComponent {
  message = '';
  apiUrl = 'http://localhost:3000/Account/1'; // Replace "1" with the actual account ID

  constructor(private http: HttpClient) {}

  fetchAccount() {
    this.http.get(this.apiUrl).subscribe({
      next: (data) => {
        this.message = JSON.stringify(data, null, 2); // Display response
      },
      error: (err) => {
        this.message = 'Error fetching account!';
        console.error(err);
      }
    });
  }
}
