import { Component, OnInit } from '@angular/core';
import { HttpClient } from '@angular/common/http';

@Component({
  selector: 'app-account',
  templateUrl: './account.component.html',
  styleUrl: './account.component.css'
})

export class AccountComponent {
  accounts: any[] = [];

  constructor(private http: HttpClient) {}

  ngOnInit(); void {}

  getAccounts(): void {
    this.http.get<any[]>('http://localhost:8080/Account').subscribe(data => this.accounts = data, error => console.error(error));

  }
}
