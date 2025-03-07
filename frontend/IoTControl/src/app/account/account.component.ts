import { Component } from '@angular/core';
import { HttpClient } from '@angular/common/http';

@Component({
  selector: 'app-account',
  templateUrl: './account.component.html',
  styleUrls: ['./account.component.css']
})
export class AccountComponent {
  accounts: any[] = []; // ✅ Define accounts as an array

  constructor(private http: HttpClient) {} // ✅ Inject HttpClient

  getAccounts() {
    this.http.get<any[]>('http://localhost:8080/Account/1') // ✅ Replace with your actual API URL
      .subscribe(response => {
        this.accounts = response; // ✅ Store API response in accounts
      }, error => {
        console.error('Error fetching accounts', error);
      });
  }
}
